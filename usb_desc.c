/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  Micha³ Budzoñ
  * @version V0.0.1
  * @date    17-August-2013
  ******************************************************************************/
#include "usb_desc.h"

/* USB Standard Device Descriptor */
const uint8_t DeviceDescriptor[DEVICE_DESC_SIZE] =
{
    DEVICE_DESC_SIZE,           /*bLength */
    DEVICE_DESCRIPTOR,			/*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x02,                       /*bDeviceClass*/
    0x01,                       /*bDeviceSubClass*/
    0x03,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40*/
    VID&0xFF,                   /*idVendor */
    VID>>8, 
    PID&0xFF,                   /*idProduct */
    PID>>8,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing manufacturer */
    2,                          /*Index of string descriptor describing product*/
    3,                          /*Index of string descriptor describing the device serial number */
    0x01                        /*bNumConfigurations*/
}; /* Composite_DeviceDescriptor */


/* USB Configuration Descriptor */
/* All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t ConfigDescriptor[CONFIG_DESC_TOTAL_SIZE] =
  {
    CONFIG_DESC_SIZE, 					/* bLength: Configuration Descriptor size */
    CONFIG_DESCRIPTOR,  /* bDescriptorType: Configuration */
    CONFIG_DESC_TOTAL_SIZE,		  		/* wTotalLength: Bytes returned */
    0x00,
    0x01,      		  					/* bNumInterfaces: 1 interface */
    0x01,      							/* bConfigurationValue: Configuration value */
    0x00,      							/* iConfiguration: Index of string descriptor describing the configuration*/
    0xC0,      							/* bmAttributes: Self powered */
    0x32,      							/* MaxPower 100 mA: this current is used for detecting Vbus */
   /************** Descriptor of interface ****************/
   /* 09 */
    INTERFACE_DESC_SIZE,   				/* bLength: Interface Descriptor size */
    INTERFACE_DESCRIPTOR,  	/* bDescriptorType: Interface descriptor type */
    0x00,       						/* bInterfaceNumber: Number of Interface */
    0x00,       						/* bAlternateSetting: Alternate setting */
    0x00,       						/* bNumEndpoints (doesn't include contrl endpoint 0)*/
    0x00,       						/* bInterfaceClass: HID */
    0x00,       						/* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,       						/* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,          						/* iInterface: Index of string descriptor */
   /******************** Descriptor of additional endpoints ******************/
   /******************** Descriptor of additional interface ********************/
  }; /* Composite_ConfigDescriptor */

/* USB String Descriptors (optional) */
const uint8_t StringLangID[STRING_LANGID_SIZE] =
{
    STRING_LANGID_SIZE,
    STRING_DESCRIPTOR,
    0x09,
    0x04
}; /* LangID = 0x0409: U.S. English */

const uint8_t StringVendor[STRING_VENDOR_SIZE] =
  {
    STRING_VENDOR_SIZE, 		 /* Size of Vendor string */
    STRING_DESCRIPTOR,  		 /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'B', 0,
	'u', 0,
	'd', 0,
	'z', 0,
	'i', 0,
	'k', 0
  };

const uint8_t StringProduct[STRING_PRODUCT_SIZE] =
  {
    STRING_PRODUCT_SIZE,       /* bLength */
    STRING_DESCRIPTOR,         /* bDescriptorType */
    'B', 0,
	'u', 0,
	'd', 0,
	'z', 0, 
	'i', 0,
	'k', 0,
	' ', 0,
	'D', 0,
	'e', 0,
	'v', 0,
    'i', 0,
	'c', 0,
	'e', 0
  };
  
const uint8_t StringSerial[STRING_SERIAL_SIZE] =
  {
    STRING_SERIAL_SIZE,           	/* bLength */
    STRING_DESCRIPTOR,     		    /* bDescriptorType */
    'B', 0,
	'D', 0,
	'Z', 0,
	' ', 0,
	'v', 0,
	'0', 0,
	'.', 0,
	'1', 0
  };
  
const uint8_t DeviceStatus[DEVICE_STATUS_SIZE] =
  {
    0x00,
	0x01
  };
