#ifndef USB_COM_H
#define USB_COM_H

#include "usb_aux.h"

#define BTableAddr				0x0
#define TxBufAddr				0x80
#define RxBufAddr				0x40

enum usbrequest_e{
    GET_PARAM = 0,
    SET_PARAM = 1
};

enum usbindex_e{
	/* SET_PARAM */
	STATE,
	STOP,
	MOVE_LEFT,
	MOVE_RIGHT,
    DRIVING,   
    SPEED, 
    WINDINGS,
	PWM,
	/* GET_PARAM */
	CURRENT
};

void Setup0(void);
void DataIn(void);
void DataOut(void);
void RequestRoutine(SetupPacket *sp);
void UserFunction(SetupPacket *sp);
static void SendResponse(void);
inline static void SendData(void);
#endif