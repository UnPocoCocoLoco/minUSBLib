#include "stm32f10x_usb.h"
#include "macros.h"

volatile uint8_t addr_g;
DEVICE_STATE device_state_g;
RESPONSE_TYPE response_type_g;
uint8_t data_size_g;

/* INTERRUPT */
USB_LP_CAN_RX0_IRQHandler()
{
	USB_Istr();
}

inline void USB_Init()
{  
  GPIO_CR(GPIOA, 12, GENERAL | OUTPUT_50 | PUSH_PULL ); // D+
  GPIO_CR(GPIOA, 11, GENERAL | OUTPUT_50 | PUSH_PULL ); // D-
  GPIO_ODR(GPIOA, 11, 0);
  GPIO_ODR(GPIOA, 12, 0);
  
  delay(100000);
  
  ENABLE_INTERRUPT(20);
  
  _SetCNTR(CNTR_FRES);   //  Pwr Up USB transceiver
  delay(3000);
  _SetCNTR(0);
  _SetISTR(0); // Clear pending interrupts /
  _SetCNTR(CNTR_CTRM | CNTR_RESETM) ;//| USB_CNTR_SOFM | USB_CNTR_ESOFM;	// Unreset USB and set interrupt's mask
  device_state_g = ATTACHED;
  
  GPIO_CR(GPIOA, 12, ALTERNATE | OUTPUT_50 | PUSH_PULL ); // D+
  GPIO_CR(GPIOA, 11, ALTERNATE | OUTPUT_50 | PUSH_PULL ); // D-
}

void USB_Istr(void)
{
	uint32_t istr = _GetISTR();
	uint32_t cntr = _GetCNTR(); // interrupt's mask
	
	if (istr & ISTR_CTR & cntr){
		CTR_LP();
	}
	if (istr & ISTR_RESET & cntr){
		USB_Reset();
	}
} /* USB_Istr */

void CTR_LP(void)
{
  uint8_t ep_num;
  uint16_t istr;
  
  /* stay in loop while pending interrupts */
  while (((istr = _GetISTR()) & ISTR_CTR) != 0)
  {
    /* extract highest priority endpoint number */
    ep_num = (uint8_t)(istr & ISTR_EP_ID);
    if (ep_num == 0)
    {
		if (!(istr & ISTR_DIR)){ // DIR == 0 -> sent (IN)
			DataIn();
		}
		else // DIR == 1 -> received(OUT)
		{
			if (_GetENDPOINT(0) & EP_SETUP){
				_ClearEP_CTR_RX(0); /* SETUP bit kept frozen while CTR_RX = 1 */
				Setup0();
			}
			else if ((_GetENDPOINT(0) & EP_CTR_RX)){ // else EP0 & EP_SETUP
				_ClearEP_CTR_RX(0);
				DataOut();
			}
		} // endif dir
    }
    else // (ep_num != 0)
    {
      /*/Decode and service non control endpoints interrupt  

      // process related endpoint register 
      wEPVal = _GetENDPOINT(EPindex);
      if ((wEPVal & EP_CTR_RX) != 0)
      {
        // clear int flag 
        _ClearEP_CTR_RX(EPindex);

        // call OUT service function 
        (*pEpInt_OUT[EPindex-1])();

      } // if((wEPVal & EP_CTR_RX) 

      if ((wEPVal & EP_CTR_TX) != 0)
      {
        // clear int flag 
        _ClearEP_CTR_TX(EPindex);

        // call IN service function 
        (*pEpInt_IN[EPindex-1])(
      } // if((wEPVal & EP_CTR_TX) != 0) 
		*/
    }// endif (ep_num == 0) else 

  }//while(...) 
}

void USB_Reset(void)
{	
	_SetISTR(~ISTR_RESET);
	_SetBTABLE(BTableAddr);
	//endpoint 0 init
	_SetEPRxCount(0, 64);
	_SetEPRxAddr(0, RxBufAddr);
	_SetEPTxAddr(0, TxBufAddr);
	// Initialize Endpoint 0 
	_ClearEP_CTR_TX(0);
	_ClearEP_CTR_RX(0);
	_SetEPType(0, EP_CONTROL);
	_ClearEP_KIND(0);
	_SetEPTxStatus(0, EP_TX_NAK);
	_SetEPRxStatus(0, EP_RX_VALID);
	// default address 0 & turn usb on
	addr_g = 0;
	device_state_g = DEFAULT;
	_EnAndSetAddr(addr_g);
}