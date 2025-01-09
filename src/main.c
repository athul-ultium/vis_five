#include <stdio.h>
#include "wl_types.h"
#include "gpio.h"

volatile uint32_t count;
void delay(uint32_t time)
{
    count = 0;
    for(uint32_t i=0; i < time; i++)
    {
        count++;
    }
}

int main(void)
{
    while(1)
    {
         gpio_write(61,1);
         delay(100000 * 500);
	 gpio_write(60,1);
         delay(100000 * 500);
         gpio_write(60,0);
         delay(100000 * 500);
         gpio_write(61,0);
         delay(100000 * 500);
    }
    return 0;
}
