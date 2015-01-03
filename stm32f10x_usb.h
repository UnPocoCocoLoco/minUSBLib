/**
  ******************************************************************************
  * @file    stm32f10x_usb.h
  * @author  Michal Budzon
  * @version V0.0.1
  * @date    10-August-2013
  * @brief   USB Access Layer Header File. 
  *          This file contains USB register's definitions, bits 
  *          definitions andPEmemory mapping for STM32F103
  ******************************************************************************
  */
    
#ifndef __STM32F10x_USB_H
#define __STM32F10x_USB_H

#include "stm32f10x.h"
#include "usb_regs.h"
#include "macros.h"
#include "usb_aux.h"
#include "usb_com.h"

#ifdef __cplusplus
 extern "C" {
#endif 

extern DEVICE_STATE device_state_g;

inline void USB_Init();
void USB_Istr(void);
void CTR_LP(void);
void USB_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_H */

/******************* (C) COPYRIGHT 2013 Budzik *****END OF FILE****/
