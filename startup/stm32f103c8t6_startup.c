#include<stdint.h>

extern uint32_t __StackTop;

void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVCall_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void Default_Handler(void)
{
 	while(1);
}

__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
	(uint32_t *) &__StackTop,
	(uint32_t *) Reset_Handler,
	(uint32_t *) HardFault_Handler,
	(uint32_t *) MemManage_Handler,
	(uint32_t *) BusFault_Handler,
	(uint32_t *) UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t *) SVCall_Handler,
	(uint32_t *) DebugMonitor_Handler,
	0,
	(uint32_t *) PendSV_Handler,
	(uint32_t *) SysTick_Handler,
};

extern uint32_t __etext, __sdata, __edata, __sbss, __ebss;
extern int main(void);

void Reset_Handler(void)
{
	uint32_t *src, *dest;
	
	src = &__etext;
	dest = &__sdata;

	while(dest < &__edata)
	{
		*dest++ = *src++;
	}
	dest = &__sbss;
	while(dest < &__ebss)
	{
		*dest++ = 0;
	}

	main();
}













