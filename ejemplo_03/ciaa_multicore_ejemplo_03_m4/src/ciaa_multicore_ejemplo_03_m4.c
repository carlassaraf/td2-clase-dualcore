/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_03_m4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_board_api.h"
#include "ciaa_ipc_api.h"

// Macros de umbrales de ADC
#define FIRST_THRESHOLD		0x3ff / 4
#define SECOND_THRESHOLD	0x3ff / 2
#define THIRD_THRESHOLD		3 * 0x3ff / 4

// Redefino zona compartida de memoria
#undef SHARED_MEM_IPC
#define SHARED_MEM_IPC	0x10086000

/**
 * @brief Programa principal
 */
int main(void) {
	// Actualizo el clock del sistema
	SystemCoreClockUpdate();
	// Inicializo los LEDs como salida
	gpio_set_dir_out(LED1);
	gpio_set_dir_out(LED2);
	gpio_set_dir_out(LED3);
	gpio_set_dir_out(LEDR);
	gpio_set_dir_out(LEDG);
	gpio_set_dir_out(LEDB);
	// Apago los LEDs
	gpio_clr(LED1);
	gpio_clr(LED2);
	gpio_clr(LED3);
	gpio_clr(LEDR);
	gpio_clr(LEDG);
	gpio_clr(LEDB);
	// Inicializo el M0
	multicore_m0_start();
	// Variable para guardar el valor del ADC
	uint16_t adc_value = 0;
	// Inicializo la RAM
	ipc_queue_init(&adc_value, sizeof(uint16_t), 1);

	while(1) {
		// Intenta hacer un pop de la RAM
		ipc_try_pop(&adc_value);
		// Verifica el umbral
		if(adc_value < FIRST_THRESHOLD) {
			// Apaga todos los LEDs
			gpio_clr(LED1);
			gpio_clr(LED2);
			gpio_clr(LED3);
		}
		else if(adc_value < SECOND_THRESHOLD) {
			// Prende el LED1
			gpio_set(LED1);
			// Apaga los LEDs 2 y 3
			gpio_clr(LED2);
			gpio_clr(LED3);
		}
		else if(adc_value < THIRD_THRESHOLD) {
			// Prende los LEDs 1 y 2
			gpio_set(LED1);
			gpio_set(LED2);
			// Apaga el LED 3
			gpio_clr(LED3);
		}
		else {
			// Prende los tres LEDs
			gpio_set(LED1);
			gpio_set(LED2);
			gpio_set(LED3);
		}
		// Imprime valor por consola
		printf("ADC value: %d\r\n", adc_value);
	}

	return 0;
}

