#ifndef _UART_H_
#define _UART_H


#define UART_BASE                 (0x10000000U)
#define LINE_STATUS_REG           (UART_BASE + 0x14U)
#define UART_BUSY_BIT             5
#define UART_DAT_REG              (UART_BASE + 0x0U)


void write_uart_single_byte(uint8_t byte);
void uart_write(char *data, uint8_t len);

#endif
