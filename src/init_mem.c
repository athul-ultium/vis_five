#include <stdio.h>
#include <stdint.h>
#include "common.h"

extern unsigned int _bss_start, _bss_end;


void bss_start() {
	    uint32_t* bss = &_bss_start;
        uint32_t* bss_end = &_bss_end;
        while (bss < bss_end) {
              *bss++ = 0;
        }
//        main();

}
