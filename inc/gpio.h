#ifndef _GPIO_H_
#define _GPIO_H_

#include "common.h"

#define GPIO_BASE          0x13040000
#define GPIO_GPIO_DOEN_REG (GPIO_BASE + 0x0)
#define GPIO_GPIO_DOUT_REG (GPIO_BASE + 0x40)


//typedef unsigned int uint;
void gpio_write(uint32_t pin, bool value);
//static void set_gpio(unsigned int pin);
//static void clear_gpio(unsigned int pin);

#endif
