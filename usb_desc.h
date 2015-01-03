/*/**
  ******************************************************************************
  * @file    usb_desc.h
  * @author  Micha³ Budzoñ
  * @version V0.0.1
  * @date    17-August-2013
  ******************************************************************************/
#ifndef USB_DESC_H
#define USB_DESC_H

#include <inttypes.h>

#define VID										0x3333						
#define PID										0x1244

#define DEVICE_DESC_SIZE		                18
#define CONFIG_DESC_SIZE         				 9
#define CONFIG_DESC_TOTAL_SIZE         			18
#define INTERFACE_DESC_SIZE						 9
#define STRING_LANGID_SIZE					     4
#define STRING_VENDOR_SIZE            			14
#define STRING_PRODUCT_SIZE            			28
#define STRING_SERIAL_SIZE             			18
#define DEVICE_STATUS_SIZE						 2
#define STANDARD_ENDPOINT_DESC_SIZE              9

typedef enum _DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIG_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

typedef enum _STANDARD_REQUESTS
{
  GET_STATUS = 0,
  CLEAR_FEATURE,
  RESERVED1,
  SET_FEATURE,
  RESERVED2,
  SET_ADDRESS,
  GET_DESCRIPTOR,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SET_CONFIGURATION,
  GET_INTERFACE,
  SET_INTERFACE,
  SYNCH_FRAME = 12
} STANDARD_REQUESTS;

extern const uint8_t DeviceDescriptor[DEVICE_DESC_SIZE];
extern const uint8_t ConfigDescriptor[CONFIG_DESC_TOTAL_SIZE];
extern const uint8_t StringLangID[STRING_LANGID_SIZE];
extern const uint8_t StringVendor[STRING_VENDOR_SIZE];
extern const uint8_t StringProduct[STRING_PRODUCT_SIZE];
extern const uint8_t StringSerial[STRING_SERIAL_SIZE];
extern const uint8_t DeviceStatus[DEVICE_STATUS_SIZE];
#endif /* USB_DESC_H */