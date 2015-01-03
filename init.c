/*----------Macro definition--------------------------------------------------*/
#define WEAK __attribute__ ((weak))
#include <inttypes.h>

/* ---------Basic functions and intterupt's routines prototypes---------------*/

extern void main(void);             /*!< The entry point for the application.    */
extern void SystemInit(void);    			/*!< Setup the microcontroller system(CMSIS) */
//core interrupts
void WEAK Reset_Handler(void);
void WEAK NMI_Handler(void);
void WEAK HardFault_Handler(void);
void WEAK MemManage_Handler(void);
void WEAK BusFault_Handler(void);
void WEAK UsageFault_Handler(void);
void WEAK SVCall_Handler(void);
void WEAK DebugMon_Handler(void);
void WEAK PendSV_Handler(void);
void WEAK SysTick_Handler(void);
//external interrupts
void WEAK WWDG_IRQHandler(void);
void WEAK PVD_IRQHandler(void);
void WEAK TAMPER_IRQHandler(void);
void WEAK RTC_IRQHandler(void);
void WEAK FLASH_IRQHandler(void);
void WEAK RCC_IRQHandler(void);
void WEAK EXTI0_IRQHandler(void);
void WEAK EXTI1_IRQHandler(void);
void WEAK EXTI2_IRQHandler(void);
void WEAK EXTI3_IRQHandler(void);
void WEAK EXTI4_IRQHandler(void);
void WEAK DMA1_Channel1_IRQHandler(void);
void WEAK DMA1_Channel2_IRQHandler(void);
void WEAK DMA1_Channel3_IRQHandler(void);
void WEAK DMA1_Channel4_IRQHandler(void);
void WEAK DMA1_Channel5_IRQHandler(void);
void WEAK DMA1_Channel6_IRQHandler(void);
void WEAK DMA1_Channel7_IRQHandler(void);
void WEAK ADC1_2_IRQHandler(void);
void WEAK USB_HP_CAN_TX_IRQHandler(void);
void WEAK USB_LP_CAN_RX0_IRQHandler(void);
void WEAK CAN_RX1_IRQHandler(void);
void WEAK CAN_SCE_IRQHandler(void);
void WEAK EXTI9_5_IRQHandler(void);
void WEAK TIM1_BRK_IRQHandler(void);
void WEAK TIM1_UP_IRQHandler(void);
void WEAK TIM1_TRG_COM_IRQHandler(void);
void WEAK TIM1_CC_IRQHandler(void);
void WEAK TIM2_IRQHandler(void);
void WEAK TIM3_IRQHandler(void);
void WEAK TIM4_IRQHandler(void);
void WEAK I2C1_EV_IRQHandler(void);
void WEAK I2C1_ER_IRQHandler(void);
void WEAK I2C2_EV_IRQHandler(void);
void WEAK I2C2_ER_IRQHandler(void);
void WEAK SPI1_IRQHandler(void);
void WEAK SPI2_IRQHandler(void);
void WEAK USART1_IRQHandler(void);
void WEAK USART2_IRQHandler(void);
void WEAK USART3_IRQHandler(void);
void WEAK EXTI15_10_IRQHandler(void);
void WEAK RTCAlarm_IRQHandler(void);
void WEAK USBWakeup_IRQHandler(void);
void WEAK TIM8_BRK_IRQHandler(void);
void WEAK TIM8_UP_IRQHandler(void);
void WEAK TIM8_TRG_COM_IRQHandler(void);
void WEAK TIM8_CC_IRQHandler(void);
void WEAK ADC3_IRQHandler(void);
void WEAK FSMC_IRQHandler(void);
void WEAK SDIO_IRQHandler(void);
void WEAK TIM5_IRQHandler(void);
void WEAK SPI3_IRQHandler(void);
void WEAK UART4_IRQHandler(void);
void WEAK UART5_IRQHandler(void);
void WEAK TIM6_IRQHandler(void);
void WEAK TIM7_IRQHandler(void);
void WEAK DMA2_Channel1_IRQHandler(void);
void WEAK DMA2_Channel2_IRQHandler(void);
void WEAK DMA2_Channel3_IRQHandler(void);
void WEAK DMA2_Channel4_5_IRQHandler(void);

/*----------Symbols defined in linker script----------------------------------*/

extern unsigned long _text_begin;     /*!< Start address for the the .text section.*/
extern unsigned long _text_end;  	  /*!< End address for the .text section       */
extern unsigned long _data_begin;     /*!< Start address for the .data section     */
extern unsigned long _data_end;       /*!< End address for the .data section       */
extern unsigned long _bss_begin;      /*!< Start address for the .bss section      */
extern unsigned long _bss_end;        /*!< End address for the .bss section        */
extern uint32_t _stack_top;               /*!< End of the stack                		   */
extern uint32_t _heap_top;                /*!< End of the heap             			   */


/*---------ISR_VECTOR section------------------------------------------------*/
unsigned int * myvectors[] 
__attribute__ ((section(".isr_vector")))= {
  /*----------Core Exceptions------------------------------------------------ */
  (void*)&_stack_top,    	 /*!< The initial stack pointer					  */
  (void *)Reset_Handler,     /*!< Reset Handler                               */
  (void *)NMI_Handler,               /*!< NMI Handler                                 */
  (void *)HardFault_Handler,         /*!< Hard Fault Handler                          */
  (void *)MemManage_Handler,         /*!< MPU Fault Handler                           */
  (void *)BusFault_Handler,          /*!< Bus Fault Handler                           */
  (void *)UsageFault_Handler,        /*!< Usage Fault Handler                         */
  0,0,0,0,                   /*!< Reserved                                    */
  (void *)SVCall_Handler,            /*!< SVCall Handler                              */
  (void *)DebugMon_Handler,          /*!< Debug Monitor Handler                       */
  0,                         /*!< Reserved                                    */
  (void *)PendSV_Handler,            /*!< PendSV Handler                              */
  (void *)SysTick_Handler,           /*!< SysTick Handler                             */
  
  /*----------External Exceptions---------------------------------------------*/
  (void *)WWDG_IRQHandler,           /*!<  0: Window WatchDog                         */
  (void *)PVD_IRQHandler,            /*!<  1: PVD through EXTI Line detection         */
  (void *)TAMPER_IRQHandler,         /*!<  2: Tamper and TimeStamps through the EXTI line*/
  (void *)RTC_IRQHandler,            /*!<  3: RTC Wakeup through the EXTI line        */
  (void *)FLASH_IRQHandler,          /*!<  4: FLASH                                   */
  (void *)RCC_IRQHandler  ,          /*!<  5: RCC                                     */
  (void *)EXTI0_IRQHandler,          /*!<  6: EXTI Line0                              */
  (void *)EXTI1_IRQHandler,          /*!<  7: EXTI Line1                              */
  (void *)EXTI2_IRQHandler,          /*!<  8: EXTI Line2                              */
  (void *)EXTI3_IRQHandler,          /*!<  9: EXTI Line3                              */
  (void *)EXTI4_IRQHandler,          /*!< 10: EXTI Line4                              */
  (void *)DMA1_Channel1_IRQHandler,  /*!< 11: DMA1 Channel 1                          */
  (void *)DMA1_Channel2_IRQHandler,  /*!< 12: DMA1 Channel 2                          */
  (void *)DMA1_Channel3_IRQHandler,  /*!< 13: DMA1 Channel 3                          */
  (void *)DMA1_Channel4_IRQHandler,  /*!< 14: DMA1 Channel 4                          */
  (void *)DMA1_Channel5_IRQHandler,  /*!< 15: DMA1 Channel 5                          */
  (void *)DMA1_Channel6_IRQHandler,  /*!< 16: DMA1 Channel 6                          */
  (void *)DMA1_Channel7_IRQHandler,  /*!< 17: DMA1 Channel 7                          */
  (void *)ADC1_2_IRQHandler,         /*!< 18: ADC1 and ADC2 global interrupt          */
  (void *)USB_HP_CAN_TX_IRQHandler,  /*!< 19: USB High Priority or CAN TX             */
  (void *)USB_LP_CAN_RX0_IRQHandler, /*!< 20: USB Low Priority or CAN RX0             */
  (void *)CAN_RX1_IRQHandler,        /*!< 21: CAN1 RX1                                */
  (void *)CAN_SCE_IRQHandler,        /*!< 22: CAN1 SCE                                */
  (void *)EXTI9_5_IRQHandler,        /*!< 23: External Line[9:5]s                     */
  (void *)TIM1_BRK_IRQHandler,		 /*!< 24: TIM1 Break             		          */
  (void *)TIM1_UP_IRQHandler, 		 /*!< 25: TIM1 Update       	                  */
  (void *)TIM1_TRG_COM_IRQHandler,	 /*!< 26: TIM1 Trigger and Commutation and TIM11  */
  (void *)TIM1_CC_IRQHandler,        /*!< 27: TIM1 Capture Compare                    */
  (void *)TIM2_IRQHandler,           /*!< 28: TIM2                                    */
  (void *)TIM3_IRQHandler,           /*!< 29: TIM3                                    */
  (void *)TIM4_IRQHandler,           /*!< 30: TIM4                                    */
  (void *)I2C1_EV_IRQHandler,        /*!< 31: I2C1 Event                              */
  (void *)I2C1_ER_IRQHandler,        /*!< 32: I2C1 Error                              */
  (void *)I2C2_EV_IRQHandler,        /*!< 33: I2C2 Event                              */
  (void *)I2C2_ER_IRQHandler,        /*!< 34: I2C2 Error                              */
  (void *)SPI1_IRQHandler,           /*!< 35: SPI1                                    */
  (void *)SPI2_IRQHandler,           /*!< 36: SPI2                                    */
  (void *)USART1_IRQHandler,         /*!< 37: USART1                                  */
  (void *)USART2_IRQHandler,         /*!< 38: USART2                                  */
  (void *)USART3_IRQHandler,         /*!< 39: USART3                                  */
  (void *)EXTI15_10_IRQHandler,      /*!< 40: External Line[15:10]s                   */
  (void *)RTCAlarm_IRQHandler,       /*!< 41: RTC Alarm (A and B) through EXTI Line   */
  (void *)USBWakeup_IRQHandler,      /*!< 42: USB wakeup frm suspend through EXTI line*/
  (void *)TIM8_BRK_IRQHandler,		 /*!< 43: TIM8 Break                              */
  (void *)TIM8_UP_IRQHandler,		 /*!< 44: TIM8 Update                             */
  (void *)TIM8_TRG_COM_IRQHandler, 	 /*!< 45: TIM8_TRG_COM                            */
  (void *)TIM8_CC_IRQHandler,		 /*!< 46: TIM8 Capture Compare                    */
  (void *)ADC3_IRQHandler,			 /*!< 47: ADC3                           		  */
  (void *)FSMC_IRQHandler,			 /*!< 48: FSMC                                    */
  (void *)SDIO_IRQHandler,           /*!< 49: SDIO                     			      */									 	
  (void *)TIM5_IRQHandler,           /*!< 50: TIM5 global interrupt                   */
  (void *)SPI3_IRQHandler,           /*!< 51: SPI3 global interrupt                   */
  (void *)UART4_IRQHandler,          /*!< 52: UART4 global interrupt				  */
  (void *)UART5_IRQHandler,          /*!< 53: UART5 global interrupt                  */
  (void *)TIM6_IRQHandler,           /*!< 54: TIM6 global interrupt                   */
  (void *)TIM7_IRQHandler,           /*!< 55: TIM7 global interrupt                   */
  (void *)DMA2_Channel1_IRQHandler,  /*!< 56: DMA2 Channel1 global interrupt          */
  (void *)DMA2_Channel2_IRQHandler,  /*!< 57: DMA2 Channel2 global interrupt          */
  (void *)DMA2_Channel3_IRQHandler,  /*!< 58: DMA2 Channel3 global interrupt          */
  (void *)DMA2_Channel4_5_IRQHandler,/*!< 59: DMA2 Channel4 global interrupt          */
};

static void Default_Handler(void)
{
	/* Go into an infinite loop. */
	while (1)
	{
	}
}

void Default_Reset_Handler(void)
{
  unsigned long *src, *dest;

  /* Copy the data segment initializers from flash to SRAM */
  src = &_text_end;
  dest = &_data_begin;
  while (dest < &_data_end) *dest++ = *src++;
  
  /* Fill bss segment with zeros */
  dest = &_bss_begin;
  while(dest < &_bss_end) *dest++ = 0; 
  
  /* Init  */
  SystemInit();
  
  /* Call the application's entry point.*/
  main();
}

#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVCall_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler

#pragma weak WWDG_IRQHandler = Default_Handler
#pragma weak PVD_IRQHandler = Default_Handler
#pragma weak TAMPER_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak FLASH_IRQHandler = Default_Handler
#pragma weak RCC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel5_IRQHandler = Default_Handler
#pragma weak DMA1_Channel6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel7_IRQHandler = Default_Handler
#pragma weak ADC1_2_IRQHandler = Default_Handler
//#pragma weak USB_HP_CAN_TX_IRQHandler = Default_Handler
//#pragma weak USB_LP_CAN_RX0_IRQHandler = Default_Handler
#pragma weak CAN_RX1_IRQHandler = Default_Handler
#pragma weak CAN_SCE_IRQHandler = Default_Handler
#pragma weak EXTI9_5_IRQHandler = Default_Handler
#pragma weak TIM1_BRK_IRQHandler = Default_Handler
//#pragma weak TIM1_UP_IRQHandler = Default_Handler
#pragma weak TIM1_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM1_CC_IRQHandler = Default_Handler
#pragma weak TIM2_IRQHandler = Default_Handler
//#pragma weak TIM3_IRQHandler = Default_Handler
#pragma weak TIM4_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak USART3_IRQHandler = Default_Handler
#pragma weak EXTI15_10_IRQHandler = Default_Handler
#pragma weak RTCAlarm_IRQHandler = Default_Handler
//#pragma weak USBWakeup_IRQHandler = Default_Handler
#pragma weak TIM8_BRK_IRQHandler = Default_Handler
#pragma weak TIM8_UP_IRQHandler = Default_Handler
#pragma weak TIM8_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM8_CC_IRQHandler = Default_Handler
#pragma weak ADC3_IRQHandler = Default_Handler
#pragma weak FSMC_IRQHandler = Default_Handler
#pragma weak SDIO_IRQHandler = Default_Handler
#pragma weak TIM5_IRQHandler = Default_Handler
#pragma weak SPI3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak UART5_IRQHandler = Default_Handler
#pragma weak TIM6_IRQHandler = Default_Handler
#pragma weak TIM7_IRQHandler = Default_Handler
#pragma weak DMA2_Channel1_IRQHandler = Default_Handler
#pragma weak DMA2_Channel2_IRQHandler = Default_Handler
#pragma weak DMA2_Channel3_IRQHandler = Default_Handler
#pragma weak DMA2_Channel4_5_IRQHandler = Default_Handler