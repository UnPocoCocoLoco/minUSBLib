#include "usb_com.h"
#include "usb_desc.h"
#include "usb_regs.h"
#include "stm32f10x.h"

extern volatile uint8_t   addr_g;
extern DEVICE_STATE       device_state_g;
extern RESPONSE_TYPE      response_type_g;
static uint8_t*           data_to_send_g;
static uint8_t            data_size_g;

void UserFunction(SetupPacket *sp)
{	/************** 
			MODIFY HERE - callback function
					***************/
		data_to_send_g[0] = 0x11; // fill this table with you data
		data_to_send_g[1] = 0x22;
		data_to_send_g[2] = 0x33;
		data_to_send_g[3] = 0x44;
		data_to_send_g[4] = 0x55;
		data_to_send_g[5] = 0x66;
		data_to_send_g[6] = 0x77;
		data_to_send_g[7] = 0x88;
		
		data_size_g = 8; // add your data length
}

void Setup0(void)
{
	static SetupPacket sp;
	PMAToPacket(&sp, RxBufAddr);  // Reading received setup data
				
	RequestRoutine(&sp);	// Performing a proper action and alternatively chosing data to send
		
	if(sp.wLength.w && (sp.bmRequestType&DATA_DIRECTION_MASK) == DEVICE_TO_HOST){
		SendData();	   // Sends data which has been pointed in Request_Routine()
	}
	else{
		SendResponse();  // Sends response which has been set in Request_Routine()
	}
}

void RequestRoutine(SetupPacket *sp)
{	
	if((sp->bmRequestType & (REQUEST_TYPE_MASK | RECIPIENT_TYPE_MASK)) == (STANDARD_REQUEST | DEVICE_RECIPIENT)){ // Device-to-host
		switch(sp->bRequest){
			case GET_STATUS: // 0
				if(sp->wValue.w == 0 && sp->wIndex.w == 0 && sp->wLength.w == 2){
					data_size_g = sp->wLength.w;
					data_to_send_g = (uint8_t*)DeviceStatus;
				}
				break;
			case GET_DESCRIPTOR: 
				switch(sp->wValue.b.h){
					case DEVICE_DESCRIPTOR:
						data_to_send_g = (uint8_t*)DeviceDescriptor;
						data_size_g = DEVICE_DESC_SIZE;
						break;
					case CONFIG_DESCRIPTOR:
						data_to_send_g = (uint8_t*)ConfigDescriptor;
						data_size_g = (sp->wLength.w > CONFIG_DESC_TOTAL_SIZE ? CONFIG_DESC_TOTAL_SIZE : sp->wLength.w);
						break;
					case STRING_DESCRIPTOR:
						switch(sp->wValue.b.l){
							case 0:
								data_to_send_g = (uint8_t*)StringLangID;
								data_size_g = STRING_LANGID_SIZE;
								break;
							case 1:
								data_to_send_g = (uint8_t*)StringVendor;
								data_size_g = STRING_VENDOR_SIZE;
								break;
							case 2:
								data_to_send_g = (uint8_t*)StringProduct;
								data_size_g = STRING_PRODUCT_SIZE;
								break;
							case 3:
								data_to_send_g = (uint8_t*)StringSerial;
								data_size_g = STRING_SERIAL_SIZE;
								break;
						}
						break;
				}
			break;
			case SET_ADDRESS: 
				addr_g = sp->wValue.b.l;
				response_type_g = ACK;
				break;
			case SET_CONFIGURATION: 
				device_state_g = CONFIGURED;
				response_type_g = ACK;
				break;
			default:
				response_type_g = STALL;
				data_to_send_g = 0;
				data_size_g = 0;
				break;
		}
	}
	else if((sp->bmRequestType & (REQUEST_TYPE_MASK | RECIPIENT_TYPE_MASK)) == (STANDARD_REQUEST | INTERFACE_RECIPIENT)){
		/* to do */	
	}
	else if((sp->bmRequestType & (REQUEST_TYPE_MASK | RECIPIENT_TYPE_MASK)) == (STANDARD_REQUEST | ENDPOINT_RECIPIENT)){
		/* to do */	
	}
	else if((sp->bmRequestType  & (REQUEST_TYPE_MASK | RECIPIENT_TYPE_MASK)) == (VENDOR_REQUEST | ENDPOINT_RECIPIENT)){
		UserFunction(sp); // User function to communicate
	}
}

static void SendResponse(void)
{
	switch(response_type_g){
		case ACK:
			_SetEPTxCount(0, 0);
			_SetEPTxStatus(0, EP_TX_VALID);
			break;
		case NACK:
			_SetEPTxStatus(0, EP_TX_NAK);
			break;
		case STALL:
			_SetEPTxStatus(0, EP_TX_STALL);
			break;
	}
}

static inline void SendData(void)
{
	if(data_to_send_g) {
		BufferToPMA(data_to_send_g, TxBufAddr, data_size_g);
		_SetEPTxCount(0, data_size_g);
		_SetEPTxStatus(0, EP_TX_VALID);
	}
	else{
		_SetEPTxStatus(0, EP_TX_STALL);
	}
}

void DataIn(void)
{
	_ClearEP_CTR_TX(0);
	if(device_state_g == DEFAULT) {
		_EnAndSetAddr(addr_g);
		device_state_g = ADDRESS;
	}
	_SetEPRxStatus(0, EP_RX_VALID);
}

void DataOut(void)
{
	_ClearEP_CTR_RX(0);
	_SetEPRxStatus(0, EP_RX_VALID);
}