MEMORY
{
	FLASH(rx)  : ORIGIN = 0x08000000, LENGTH = 64K
	SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

 /**  stack setttings **/
	
	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM);
	
 /**  SECTIONS **/

SECTIONS
{
	.text :
	{
		_text_begin = .;
		*(.isr_vector)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_text_end = .;
	} > FLASH
	
	.data :
	{
		_data_begin = .;
		. = ALIGN(4);
		*(.data)
		*(.data.*);
		. = ALIGN(4);
		_data_end = .;
	} > SRAM AT>FLASH
	
	.bss :
	{
		_bss_begin = .;
		. = ALIGN(4);
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		_bss_end = .;
	} > SRAM AT>FLASH
	
	.heap :
	{
		. = ALIGN(4);
		_heap_top = .;
	} > SRAM
}
