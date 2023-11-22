/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_01_m0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_gpio_api.h"
#include "ciaa_stdlib.h"

int main(void) {

	SystemCoreClockUpdate();

	gpio_set_dir_out(LED2);
	gpio_clr(LED2);

	while(1) {

		gpio_xor(LED2);
		sleep_ms(1000);

	}
}
