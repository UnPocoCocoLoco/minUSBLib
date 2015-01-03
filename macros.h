#ifndef MACROS_H
#define MACROS_H

#include "stm32f10x.h"

///********************************************** GPIO module *********************************************///
/*!<** CNFy[1:0] if MODE[1:0]==00 **/
#define ANALOG			0 //(0<<2)
#define FLOATING		4 //(1<<2)
#define PULL_UP			8 //(2<<2)
/*!<** CNFy[1:0] if MODE[1:0]>00 ***/
#define ALTERNATE		8 //(2<<2)
#define GENERAL			0 //(0<<2)
#define PUSH_PULL		0 //(0<<2)
#define OPEN_DRAIN		4 //(1<<2)
/*!<** MODEy[1:0] *****************/
#define INPUT		0
#define OUTPUT_10	1
#define OUTPUT_2	2
#define OUTPUT_50	3

static inline void GPIO_CR(GPIO_TypeDef* port, uint8_t pin, uint8_t cnf_mode)
{
	uint32_t port_value = *(uint32_t*)((uint32_t)port + ((pin/8) << 2));
	port_value &= ~(0x0F << ((pin%8)<<2));
	port_value |= cnf_mode << ((pin%8)<<2);
	*(uint32_t*)((uint32_t)port + ((pin/8) << 2)) = port_value;
}

static inline void GPIO_ODR(GPIO_TypeDef* port, uint8_t pin, uint8_t state)
{
	*(volatile uint8_t*)(PERIPH_BB_BASE + (((uint32_t)port - PERIPH_BASE + 0x0C)<<5) + (pin<<2)) = state;
}

static inline uint16_t GPIO_IDR(GPIO_TypeDef* port)
{
	return *(volatile uint16_t*)(((uint32_t)port + 0x08));
}

///********************************************* INTERRUPTS module *********************************************///
#define ENABLE_INTERRUPT(x) (NVIC->ISER[(x) / 32] = 1 << ((x) % 32))


//************************************************ FUNCTIONS ***************************************************///
static inline void GPIOInit()
{
  GPIO_CR(GPIOC, 13, GENERAL | OUTPUT_50 | PUSH_PULL );
  GPIO_CR(GPIOB, 10, GENERAL | OUTPUT_50 | PUSH_PULL );
  /* ADC */
  GPIO_CR(GPIOB, 0, ALTERNATE | INPUT     | FLOATING );   // ADC INPUT
  
  GPIO_CR(GPIOA, 8, ALTERNATE | OUTPUT_50 | PUSH_PULL ); // wyjscie zegara
  
  GPIO_ODR(GPIOC, 13, 0); // LCD Chip enable
  //GPIO_ODR(GPIOA, 0, 1);  // 
  //GPIO_ODR(GPIOA, 1, 1);
}

static inline void SysTickInit(uint32_t counter)
{
  SysTick->LOAD  = counter;                         			      /* set reload register */
  SysTick->VAL   = 0;                                       	  	  /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE | SysTick_CTRL_ENABLE; 	  /* Enable SysTick and select clk source */
}

static inline void delay(uint32_t del)
{
	SysTickInit(del);
	while(!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG));
	SysTick->CTRL = 0;
}

static inline void PLLInit()
{
	RCC->CFGR |= RCC_CFGR_PLLMULL9  		// mnoznik PLL x9
				 | RCC_CFGR_PLLSRC_HSE  	// ustawienie Ÿródla PLL na HSE
				 | RCC_CFGR_PPRE1_2			// przeskaler APB1
				; 			 
	RCC->CR |= RCC_CR_PLLON;				// w³aczenie PLL
	while(!(RCC->CR & RCC_CR_PLLRDY)); 		// oczekiwanie na stabilny sygna³ zegarowy
	RCC->CFGR |= RCC_CFGR_SW_PLL;			// ustawienie PLL jako sygna³ systemowego
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)); // oczekiwanie na ustawienie
}

static inline void ClockInit()
{
	RCC->CR = RCC_CR_HSEON;					// w³aczenie external crystal
	while(!(RCC->CR & RCC_CR_HSERDY)); 		// oczekiwanie na gotowosc HSE
	
	FLASH->ACR |= FLASH_ACR_LATENCY_2; 		// w³¹czenie opóŸnienia pamiêci (bez tego nie pójdzie wiecej ni¿ 64Mhz)
	
	PLLInit();
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;		// a8 wyjscie zegara
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_ADC1EN | RCC_APB2ENR_TIM1EN; // w³aczenie portu A, C i alternatywnych funkcji
	RCC->APB1ENR |= RCC_APB1ENR_USBEN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;
}	

static inline void ADCInit()
{
	RCC->CFGR |= RCC_CFGR_ADCPRE_1; // :6 prescaler
	ADC1->CR2 = ADC_CR2_ADON | ADC_CR2_RSTCAL | ADC_CR2_CONT;
	while(ADC1->CR2 & ADC_CR2_RSTCAL);
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL);
	ADC1->SQR3 = ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_2; // channel 7 first and only one
	ADC1->SMPR1 = ADC_SMPR1_SMP16_2 | ADC_SMPR1_SMP16_1 | ADC_SMPR1_SMP16_0;
	delay(2000);
	ADC1->CR2 |= ADC_CR2_ADON;
	delay(2000);
	ADC1->CR2 |= ADC_CR2_ADON;
	delay(2000);
}

static inline void PWMInit()
{
	/* TIM1 & TIM3 connected timers */
	/*master 1*/
	TIM1->CR1 |= TIM_CR1_URS | TIM_CR1_OPM;
	TIM1->CR2 |= TIM_CR2_MMS_1 | TIM_CR2_MMS_0; 	// OC1REF is usead as TRGO
	TIM1->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_TS_1;
	TIM1->ARR = 65535;		   		// overflow triggers TIM3
	//TIM1->PSC = 1; // 72Mhz to 36Mhz
	
	
	/*slave 3*/
	TIM3->CR1  |= TIM_CR1_URS | TIM_CR1_OPM;
	TIM3->CR2 |= TIM_CR2_MMS_1 | TIM_CR2_MMS_0; 	// OC1REF is usead as TRGO
	TIM3->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1;		// update triggers, TRGO1 as input
	TIM3->ARR = 65000;	   // Auto reload value
	TIM3->PSC  = 65535;
	TIM3->DIER |= TIM_DIER_UIE; // Enable update interrupt (timer level)

	TIM3->EGR  |= TIM_EGR_UG;
	TIM1->EGR  |= TIM_EGR_UG;
	
	ENABLE_INTERRUPT(29);
	ENABLE_INTERRUPT(25);
	
	/* PWM */
	TIM2->ARR = 1500;
	TIM4->ARR = 1500;

	TIM4->CCMR1 = TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_2 | /*TIM_CCMR1_OC2M_1 |*/ TIM_CCMR1_OC2PE;
	
	TIM4->CCMR2 = TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_2 | /*TIM_CCMR1_OC2M_1 |*/ TIM_CCMR2_OC3PE;
	
	TIM2->CCMR2 = TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_2 | /*TIM_CCMR2_OC3M_1 |*/ TIM_CCMR2_OC3PE
				| TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_2 | /*TIM_CCMR2_OC4M_1 |*/ TIM_CCMR2_OC4PE;
	TIM2->CCER = TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM4->CCER = TIM_CCER_CC2E | TIM_CCER_CC3E;
	TIM2->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM4->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM2->EGR = TIM_EGR_UG;
	TIM4->EGR = TIM_EGR_UG;
	/* compare register initial values */
	TIM4->CCR2 = 1500;
	TIM4->CCR3 = 1500;
	TIM2->CCR3 = 1500;
	TIM2->CCR4 = 1500;
}

#endif // MACROS_H