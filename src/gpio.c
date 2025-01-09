
#include "gpio.h"
#include "wl_types.h"


static void set_gpio(uint32_t pin)
{
    // max available pin is upto 63 (total 64)
    if (pin > 63)
        return;

    uint32_t offset = (pin >> 2) * 4;
    uint32_t shift  = ((pin & 0x3) << 3);
    

    WL_CLEAR_BITS_REG32((GPIO_GPIO_DOEN_REG + offset), (0x3F << shift)); 

    /* clearing the gpio register for the pin */
    WL_CLEAR_BITS_REG32((GPIO_GPIO_DOUT_REG + offset), (0x7f << shift));    
    WL_SET_BITS_REG32((GPIO_GPIO_DOUT_REG + offset),(1 << shift));
}

static void clear_gpio(uint32_t pin)
{
    if (pin > 63)
        return;

    uint32_t offset = (pin >> 2) * 4;
    uint32_t shift  = ((pin & 0x3) << 3);

    WL_CLEAR_BITS_REG32((GPIO_GPIO_DOUT_REG + offset), (0x7f << shift));
}


void gpio_write(uint32_t pin, bool value)
{
    if (value)
    {
        set_gpio(pin);
    }
    else
    {
        clear_gpio(pin);
    }
}
