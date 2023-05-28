#include <stdint.h>


#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE	        (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOB_OFFSET 			(0x0400UL)
#define GPIOB_BASE				(AHB1PERIPH_BASE + GPIOB_OFFSET)


#define RCC_OFFSET 				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIODEN					(1U<<1) //assigned 1 to bit 1

#define PIN14					(1U<<14) // assigned 1 to bit 14
#define LED_PIN					PIN14

#define _IO 					volatile


typedef struct
{
	uint32_t DUMMY[12];
	_IO uint32_t AHB1ENR;
}RCC_TypeDef;


typedef struct
{
	_IO uint32_t MODER;
	 uint32_t DUMMY[4];
	_IO uint32_t ODR;

}GPIO_TypeDef;

#define RCC			((RCC_TypeDef*) RCC_BASE)
#define GPIOB		((GPIO_TypeDef*) GPIOB_BASE)



int main(void)
{
	RCC->AHB1ENR |= GPIODEN;

	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &=~(1U<<29);
	while(1)
	{
		GPIOB->ODR ^= LED_PIN;

		for(int i=0;i<100000;i++){}
	}
}
