// LED PB14
//port : B
//pin: 14
#include <stdint.h>
#include <stm32f4xx.h>


#define GPIODEN			(1U<<1)
#define GPIOCEN			(1U<<2)

#define PIN13			(1U<<13)
#define PIN14			(1U<<14)
#define LED_PIN			PIN14
#define BTN_PIN			PIN13

int main(void)
{
	/*Enable clock access to GPIOB and GPIOC */
	RCC->AHB1ENR |= GPIODEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PB14 as output pin */
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &=~(1U<<29);

	/*Set PC13 as output pin */
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);
	while(1)
	{
		if (GPIOC->IDR & BTN_PIN )
		{
			GPIOB->BSRR ^= LED_PIN;
		}
		else
		{
			GPIOB->BSRR = (1U<<30);
		}
	}
}
