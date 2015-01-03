#include "usb_aux.h"
#include "usb_regs.h"

void BufferToPMA(const uint8_t *buf, uint16_t Addr, uint16_t length)
{
  uint32_t n = (length + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32_t i, temp1, temp2;
  uint16_t *PMAptr = (uint16_t*)(Addr*2 + PMAAddr);
  while (n--)
  {
    temp1 = (uint16_t) * buf;
    buf++;
    temp2 = temp1 | (uint16_t) * buf << 8;
    *PMAptr++ = temp2;
    PMAptr++;
    buf++;
  }
}

void PMAToPacket(SetupPacket *sp, uint16_t Addr)
{
	uint8_t *PMAptr = (uint8_t *)(Addr*2 + PMAAddr);
	sp->bmRequestType = *PMAptr++; /* bmRequestType */
    sp->bRequest = *PMAptr++; /* bRequest */
    PMAptr+=2;  /* word not accessed because of 32 bits addressing */
    sp->wValue.b.l = *PMAptr++; /* wValue */
	sp->wValue.b.h = *PMAptr++;
    PMAptr+=2;  /* word not accessed because of 32 bits addressing */
    sp->wIndex.b.l = *PMAptr++; /* wValue */
	sp->wIndex.b.h = *PMAptr++;
    PMAptr+=2;  /* word not accessed because of 32 bits addressing */
    sp->wLength.b.l = *PMAptr++; /* wLength */
	sp->wLength.b.h = *PMAptr++; /* wLength */
 }