/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_01_m4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_gpio_api.h"
#include "ciaa_stdlib.h"
#include "ciaa_multicore_api.h"

int main(void) {

    SystemCoreClockUpdate();

    gpio_set_dir_out(LED1);
    gpio_clr(LED1);

    multicore_m0_start();

    while(1) {

    	gpio_xor(LED1);
    	sleep_ms(500);

    }
    return 0 ;
}
