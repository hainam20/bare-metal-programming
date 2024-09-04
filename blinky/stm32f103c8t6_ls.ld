



MEMORY 
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64k
	RAM (rwx): ORIGIN = 0x20000000, LENGTH = 20k
}


ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text*)
		*(.rodata*)
		__etext = ALIGN(4);
	} > FLASH

	.data : AT(__etext)
	{
		__sdata = .;
		*(.data*)
		__edata = .;
	} > RAM

	.bss :
	{
		__sbss = .;
		*(.bss*)
		__ebss = .;
	} > RAM

	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
}



