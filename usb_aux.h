#ifndef USB_AUX_H
#define USB_AUX_H

#include <inttypes.h>

/*******************************************************************************
* Macro Name     : _EnAndSetAddr.
* Description    : Enable USB and sets device address.
* Input          : bAddr: Address. 
* Output         : None.
* Return         : None.
*******************************************************************************/
#define _EnAndSetAddr(Addr) (_SetDADDR(DADDR_EF | Addr))

#define DATA_DIRECTION_MASK		0x80
#define REQUEST_TYPE_MASK		0x60
#define RECIPIENT_TYPE_MASK		0x1F

typedef union
{
  uint16_t w;
  struct BW  { uint8_t l; uint8_t h; } b;
} uint16_t_uint8_t;

typedef struct _SETUP_PACKET { 
  uint8_t bmRequestType; 		// Size of this descriptor in bytes
  uint8_t bRequest; 			// Specific Request=
  uint16_t_uint8_t wValue; 				// Use varies according to request=
  uint16_t_uint8_t wIndex; 				// Use varies according to request=
  uint16_t_uint8_t wLength; 			// Device_Descriptor;
} SetupPacket;

typedef enum _RESPONSE_TYPE {
  NACK  = 0,
  ACK   = 1,
  STALL = 2,
 } RESPONSE_TYPE;
 
typedef enum _DEVICE_STATE {
  UNATTACHED = 0,
  ATTACHED   = 1,
  POWERED    = 2,
  DEFAULT    = 3,
  ADDRESS    = 4,
  CONFIGURED = 5,
  SUSPENDED  = 6
 } DEVICE_STATE;
 
 typedef enum _RECIPIENT_TYPE
{
  DEVICE_RECIPIENT = 0,     /* Recipient device */
  INTERFACE_RECIPIENT,  /* Recipient interface */
  ENDPOINT_RECIPIENT,   /* Recipient endpoint */
  OTHER_RECIPIENT
} RECIPIENT_TYPE;

typedef enum _DATA_DIRECTION
{
  HOST_TO_DEVICE = 0x00,
  DEVICE_TO_HOST = 0x80,
} DATA_DIRECTION;

typedef enum _REQUEST_TYPE
{
  STANDARD_REQUEST  = 0x00,
  CLASS_REQUEST 	= 0x20,
  VENDOR_REQUEST 	= 0x40
} REQUEST_TYPE;

void PMAToPacket(SetupPacket *sp, uint16_t Addr);
void BufferToPMA(const uint8_t *buf, uint16_t Addr, uint16_t length);

#endif