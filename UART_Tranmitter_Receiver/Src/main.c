#include <stdint.h>
#include <stm32f4xx.h>


#define GPIODEN			(1U<<3)

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define UART3EN			(1U<<18) // port B14 for USART is 3_CTS and B13 is 3RTS under AF7

#define SYS_FREQ		16000000

#define APB1_CLK		SYS_FREQ

#define	UART_BAUDRATE	115200


static void uart_set_baudrate(USART_TypeDef *Usartx, uint32_t perphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t perphClk, uint32_t BaudRate);

void uart3_tx_init(void);
void uart3_write(int ch);

int main(void)
{
	uart3_tx_init();
	while(1)
	{
		uart3_write('Y');
	}
}


void uart3_tx_init(void)
{
	//Enable Clock access to GPIOD
	RCC->AHB1ENR |= GPIODEN;

	//set PB10 mode to alternate function mode
	GPIOD->MODER &=~ (1U<<16);
	GPIOD->MODER |=  (1U<<17);

	// set the GPIO alternate function low register to AF7
	GPIOD->AFR[1] |= (1U<<0);
	GPIOD->AFR[1] |= (1U<<1);
	GPIOD->AFR[1] |= (1U<<2);
	GPIOD->AFR[1] &= ~(1U<<3);

	/* Configure UART module */

	// Enable clock access
	RCC->APB1ENR = UART3EN;

	// Configure BaudRate
	uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

	// configure the transfer direction
	USART3->CR1 = CR1_TE;

	// Enable UART module
	USART3->CR1 |= CR1_UE;
}

void uart3_write(int ch)
{
	//Make sure USART transmit data is empty
	while (!(USART3->SR & SR_TXE)){}
	//Write to transmit data register
	USART3->DR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}



