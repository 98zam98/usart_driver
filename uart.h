
#ifndef UART_HAL_H_
#define UART_HAL_H_


#include <stdint.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "hardware.h"

#define RX_BUFFER_SIZE 128

void uart_init();
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c,uint16_t len);
void uart_send_string(uint8_t *c);
uint16_t uart_read_count(void);
uint8_t uart_read(void);

//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 











// usart_control_status_register_A functions =========================================================

// usart_receive_complete
#define check_usart_receive_complete() checkbit0(usart_control_status_register_A, usart_receive_complete)

// usart_transmit_complete
#define check_usart_transmit_complete() checkbit0(usart_control_status_register_A, usart_transmit_complete)

#define clear_usart_transmit_complete() usart_control_status_register_A &= usart_transmit_complete

// usart_data_register_empty
#define check_usart_data_register_empty() checkbit0(usart_control_status_register_A, usart_data_register_empty)

// usart_Frame_err
#define check_usart_Frame_err() checkbit0(usart_control_status_register_A, usart_Frame_err)

// usart_data_over_run
#define check_usart_data_over_run() checkbit0(usart_control_status_register_A, usart_data_over_run)

// usart_Parity_err
#define check_usart_Parity_err() checkbit0(usart_control_status_register_A, usart_Parity_err)

// usart_err                         ==============================================
void check_usart_err();

// usart_x2

typedef enum
{
    x2_Reserved,
    x2_yes,
    x2_no,
} usart_x2_mode;


#define Configure_usart_x2()   usart_control_status_register_A |= ((zUART0.zusart_x2_mode) & 1) << usart_x2;

// usart_multi_processor_communication

typedef enum
{
    multi_processor_no,
    multi_processor_yes,
} usart_multi_processor_communication_mode;
#define Configure_usart_multi_processor_communication()     usart_control_status_register_A |= zUART0.zusart_multi_processor_communication_mode << usart_multi_processor_communication

// usart_control_status_register_B functions =========================================================

// usart_receive_complete_int_en
#define enable_usart_receive_complete_int() setbit(usart_control_status_register_B, usart_receive_complete_int_en)
#define disable_usart_receive_complete_int() clearbit(usart_control_status_register_B, usart_receive_complete_int_en)

// usart_transmit_complete_int_en
#define enable_usart_transmit_complete_int() setbit(usart_control_status_register_B, usart_transmit_complete_int_en)
#define disable_usart_transmit_complete_int() clearbit(usart_control_status_register_B, usart_transmit_complete_int_en)

// usart_data_register_empty_int_en
#define enable_usart_data_register_empty_int() setbit(usart_control_status_register_B, usart_data_register_empty_int_en)
#define disable_usart_data_register_empty_int() clearbit(usart_control_status_register_B, usart_data_register_empty_int_en)

typedef enum
{
    int_Disabled,
    int_enable_all,
    int_enable_rx_tx,
    int_enable_tx_empty,
    int_enable_empty_rx,
    int_enable_rx,
    int_enable_tx,
    int_enable_empty,
} usart_int_mode;

void Configure_usart_int();

typedef enum
{
    transmit_receive_mode_Disabled,
    transmit_receive_mode_transmit,
    transmit_receive_mode_receive,
    transmit_receive_mode_both,
} usart_transmit_receive_mode;

#define Configure_usart_transmit_receive_mode() usart_control_status_register_B |= zUART0.zusart_transmit_receive_mode << usart_transmit_en

// usart_control_status_register_C functions =========================================================

// usart_CH_size

void select_usart_CH_size();

typedef enum
{
    CH_size_5,
    CH_size_6,
    CH_size_7,
    CH_size_8,
    CH_size_9,
} usart_CH_size;

// usart_stop_bit

typedef enum
{
    stop_1_bit,
    stop_2_bit,
} usart_stop_bit_mode;

#define Configure_usart_stop_bit() usart_control_status_register_C |= zUART0.zusart_stop_bit_mode << usart_stop_bit

// usart_parity_mode

typedef enum
{
    parity_Disabled,
    parity_Reserved,
    parity_even,
    parity_odd,
} usart_parity_mode;

#define Configure_usart_parity_mode() usart_control_status_register_C |= zUART0.zusart_parity_mode << usart_parity_mode_BIT_0

//  usart_mode

typedef enum
{
    usart_Asynchronous,
    usart_Synchronous,
    usart_Reserved,
    usart_Master_SPI,
} usart_mode;

#define select_usart_mode() usart_control_status_register_C |= zUART0.zusart_mode << usart_mode_select_BIT_0

// usart_baud_rate_register               ==============================================================
void set_usart_baud_rate_register(unsigned long ubrr);

typedef struct
{

    //unsigned long						                    BaudRate;
    usart_mode zusart_mode;
    usart_parity_mode zusart_parity_mode;
    usart_stop_bit_mode zusart_stop_bit_mode;
    usart_CH_size zusart_CH_size;
    usart_int_mode zusart_int_mode;
    usart_transmit_receive_mode zusart_transmit_receive_mode;
    usart_multi_processor_communication_mode zusart_multi_processor_communication_mode;
    usart_x2_mode zusart_x2_mode;
    uint32_t    zusart_baud;
    /* Make The Pointer points to a Function you wish to be Called by RXC Interrupt */
    void (*usart_receive_Interrupt_Handler)(void);
    /* Make The Pointer points to a Function you wish to be Called by TXC Interrupt */
    void (*usart_transmit_Interrupt_Handler)(void);
    /* Make The Pointer points to a Function you wish to be Called by UDRE Interrupt */
    void (*usart_data_register_empty_Interrupt_Handler)(void);
} USART_ConfigurationStruct;

extern USART_ConfigurationStruct zUART0;















//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 

//=========================================================== //=========================================================== //=========================================================== 



















#endif /* UART_HAL_H_ */