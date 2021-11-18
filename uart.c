
#include "uart.h"
#include "hardware.h"


volatile static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rx_count = 0;	
volatile static uint8_t uart_tx_busy = 1;



void usart_receive_Interrupt_Handler_FUNCTION()
{

	volatile static uint16_t rx_write_pos = 0;

	rx_buffer[rx_write_pos] = usart_data_buffer_register;
	rx_count++;
	rx_write_pos++;
	if (rx_write_pos >= RX_BUFFER_SIZE)
	{
		rx_write_pos = 0;
	}
}

void usart_transmit_Interrupt_Handler_FUNCTION()
{
	uart_tx_busy = 1;
}




#define NULL_PTR		((void *)0x00)

USART_ConfigurationStruct zUART0 = {0,
                                   .usart_receive_Interrupt_Handler = usart_receive_Interrupt_Handler_FUNCTION,
                                   .usart_transmit_Interrupt_Handler = usart_transmit_Interrupt_Handler_FUNCTION,
                                   .usart_data_register_empty_Interrupt_Handler = NULL_PTR};




ISR(usart_receive_Interrupt_vect)
{
	if ( zUART0.usart_receive_Interrupt_Handler != NULL_PTR)
	{
		zUART0.usart_receive_Interrupt_Handler();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}



ISR(usart_transmit_Interrupt_vect)
{
	if ( zUART0.usart_transmit_Interrupt_Handler != NULL_PTR)
	{
		zUART0.usart_transmit_Interrupt_Handler();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

ISR(usart_data_register_empty_Interrupt_vect)
{
	if ( zUART0.usart_data_register_empty_Interrupt_Handler != NULL_PTR)
	{
		zUART0.usart_data_register_empty_Interrupt_Handler();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}




void select_usart_CH_size()
{
    //zUART0.zusart_CH_size
    if (zUART0.zusart_CH_size == CH_size_9)
    {
        setbit(usart_control_status_register_C, usart_CH_size_BIT_0);
        setbit(usart_control_status_register_C, usart_CH_size_BIT_1);
        setbit(usart_control_status_register_C, usart_CH_size_BIT_2);
    }
    else
    {
        usart_control_status_register_C |= zUART0.zusart_CH_size << usart_CH_size_BIT_0;
    }
}



void Configure_usart_int()
{
	switch (zUART0.zusart_int_mode)
	{
	case int_Disabled:
		disable_usart_receive_complete_int();
		disable_usart_transmit_complete_int();
		disable_usart_data_register_empty_int();
		break;

	case int_enable_all:
		enable_usart_data_register_empty_int();
		enable_usart_transmit_complete_int();
		enable_usart_receive_complete_int();
		break;

	case int_enable_rx_tx:
		enable_usart_transmit_complete_int();
		enable_usart_receive_complete_int();
		break;

	case int_enable_tx_empty:
		enable_usart_data_register_empty_int();
		enable_usart_transmit_complete_int();
		break;

	case int_enable_empty_rx:
		enable_usart_data_register_empty_int();
		enable_usart_receive_complete_int();
		break;

	case int_enable_rx:
		enable_usart_receive_complete_int();
		break;

	case int_enable_tx:
		enable_usart_transmit_complete_int();
		break;

	case int_enable_empty:
		enable_usart_data_register_empty_int();
		break;

	default:
		break;
	}
}


void set_usart_baud_rate_register(uint32_t baud)
{
	usart_baud_rate_register_high = (baud & 0x0F00) >> 8;
	usart_baud_rate_register_low = (baud & 0x00FF);
}

void uart_init()
{

	uint8_t speed = 8;
	Configure_usart_x2();

	//uint32_t baud = (F_CPU / ((speed * (zUART0.zusart_x2_mode)) * (zUART0.zusart_baud))) - 1;
	set_usart_baud_rate_register((F_CPU / ((speed * (zUART0.zusart_x2_mode)) * (zUART0.zusart_baud))) - 1);
	//usart_control_status_register_B |= (1 << usart_transmit_en) | (1 << usart_receive_en) | (1 << usart_transmit_complete_int_en) | (1 << usart_receive_complete_int_en);
	select_usart_mode();
	Configure_usart_multi_processor_communication();
	select_usart_CH_size();
	Configure_usart_parity_mode();
	Configure_usart_stop_bit();
	Configure_usart_int();
	Configure_usart_transmit_receive_mode();
}

void uart_send_byte(uint8_t c)
{
	while (uart_tx_busy == 0)
		;
	uart_tx_busy = 0;
	usart_data_buffer_register = c;
}



void uart_send_array(uint8_t *c, uint16_t len)
{
	uint16_t i;
	for (i = 0; i < len; i++)
	{
		uart_send_byte(c[i]);
	}
}

void uart_send_string(uint8_t *c)
{
	uint16_t i = 0;
	do
	{
		uart_send_byte(c[i]);
		i++;

	} while (c[i] != '\0');
	uart_send_byte(c[i]);
}

uint16_t uart_read_count(void)
{
	return rx_count;
}

uint8_t uart_read(void)
{
	static uint16_t rx_read_pos = 0;
	uint8_t data = 0;

	data = rx_buffer[rx_read_pos];
	rx_read_pos++;
	rx_count--;
	if (rx_read_pos >= RX_BUFFER_SIZE)
	{
		rx_read_pos = 0;
	}
	return data;
}
