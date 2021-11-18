/*
 * leddriver.c
 *
 * Created: 2/28/2019 2:12:17 PM
 *  Author: Moatasem el sayed
 */

#include "config.h"
#include "led.h"
#include "led.c"
#include "macros.h"
#include "hardware.h"
#include <avr/interrupt.h>
#include "uart.h"
#include "uart.c"

int main()
{
  led_init();

  zUART0.zusart_x2_mode = x2_no;
  zUART0.zusart_baud = 9600;
  zUART0.zusart_mode = usart_Asynchronous;
  zUART0.zusart_multi_processor_communication_mode = multi_processor_no;
  zUART0.zusart_int_mode = int_enable_rx_tx;
  zUART0.zusart_transmit_receive_mode = transmit_receive_mode_both;
  zUART0.zusart_CH_size = CH_size_8;
  zUART0.zusart_parity_mode = parity_Disabled;
  zUART0.zusart_stop_bit_mode = stop_1_bit;
  const uint8_t start[] = "ZAM Program Start\n\r";
  uint8_t data = 'A';

  uart_init();
  sei();

  uart_send_string(start);
  while (1)
  {

    if (uart_read_count() > 0)
    {
      data = uart_read();
      uart_send_byte(data);
    }
    if ((data >= '1') && (data <= '9'))
    {
      led_ontooff((data - 48), (58 - data));
    }
    else if (data == 'b')
    {
      led_on();
    }
    else if (data == 'd')
    {
      led_off();
    }
    else if (data == 'a')
    {
      led_toggle();
    }
  }
  return 0;
}
//void led_ontooff(char on,char off);
