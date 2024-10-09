#include "stm32f103xx_gpio_driver.h"

void delay()
{
	for(int i = 0; i < 500000; i++);
}


int main()
{
	GPIO_PinConfig_t LED;
	LED.GPIO_PinNumber = GPIO_PIN_NO_13;
	LED.GPIO_PinMode = GPIO_OUT_PP;
	LED.GPIO_PinSpeed = GPIO_Speed_50Mhz;
	
	GPIO_PeriClockControl(GPIOC, ENABLE);
	GPIO_Init(GPIOC, &LED);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
		delay();	
	}

	return 0;


}
