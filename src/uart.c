#include "common.h"
#include "wl_types.h"
#include "uart.h"

void write_uart_single_byte(uint8_t byte)
{
    // waiting for ready bit to set
    while (!(WL_REG32(LINE_STATUS_REG) >> UART_BUSY_BIT));
    WL_WRITE_REG32(UART_DAT_REG,byte);
}


void uart_write(char *data, uint8_t len)
{
      for (uint8_t i = 0; i < len; i++)
      {
	     write_uart_single_byte(data[i]);
      }
}

