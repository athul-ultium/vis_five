#ifndef _WL_TYPES_H_
#define _WL_TYPES_H_

#define WL_REG32(x)                    (*(volatile uint32_t *)(x))
#define WL_WRITE_REG32(reg,val)        (WL_REG32(reg) = (val))
#define WL_SET_BITS_REG32(reg,val)     (WL_REG32(reg) |= (val))
#define WL_CLEAR_BITS_REG32(reg, val)  (WL_REG32(reg) = (WL_REG32(reg) &~(val)))
#endif
