/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_03_m0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_adc_api.h"
#include "ciaa_ipc_api.h"

// Redefino zona compartida de memoria
#undef SHARED_MEM_IPC
#define SHARED_MEM_IPC	0x10086000

/**
 * @brief Programa principal
 */
int main(void) {
	// Actualizo clock del sistema
	SystemCoreClockUpdate();
	// Estructura de configuracion del ADC
	adc_config_t adc_config = adc_get_default_config();
	// Configuro el ADC0
	adc_config_init(0, adc_config);
	// Elijo el canal
	adc_select_input(0, ADC_CH0);
	// Variable para guardar el valor del ADC
	uint16_t adc_value;
	// Reservo la RAM para la comunicacion
	ipc_queue_init(&adc_value, sizeof(uint16_t), 1);

	while(1) {
		// Leo el canal cero
		adc_value = adc_read(0);
		// Pusheo en la memoria el valor
		ipc_try_push(&adc_value);
	}

	return 0;
}
