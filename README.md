minUSBLib
=========

Minimalistic USB library for STM32F103

This minimalistic library allows simple USB communication using only control packets:
usb_regs.h - definition of registers ans basic macro functions.
usb_desc - descriptors configuration. You may change them.
usb_com  - USB communication implementation. You should modify UserFunction to send your data.
usb_aux  - Some additional macros and types declarations.
stm32f10x_usb  - High level functions to init USB and handle interrupt.

How to use it?
Include "stm32f10x_usb.h" header in main. Edit UserFunction in usb_com.c to precise communication policy.
UserFunction is a callback function called every time when Control Packet with Endpoint Recipient and Vendor Request is received.
If you use <a href="libusbx.org"> libusbX as PC's USB host library</a>, which I strongly recommend, you should send following exemplary packet:br>

libusb_control_transfer ( handle,
LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_VENDOR|LIBUSB_RECIPIENT_ENDPOINT,
request_type,
value,
index,
data_ptr,// should be NULL 
data_length, // should be 0 
timeout);

Where request_type, value and index are yout data and data_ptr and data_length should be 0. It is simplest possible comunication by USB.<br>
Next, sent structure is available in UserFunction under *sp pointer:

typedef struct _SETUP_PACKET {
  uint8_t bmRequestType; 	 // request type... this is what was sent as second parameter of libusb_control_transfer
  uint8_t bRequest; 		 // request_type
  uint16_t wValue; 			 // value
  uint16_t wIndex; 			 // index
  uint16_t wLength; 		 // data_length
} SetupPacket;
If you want to extend your knowledge about USB please look http://www.beyondlogic.org/usbnutshell/usb1.shtml and http://www.usbmadesimple.co.uk/
