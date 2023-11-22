/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_02_m0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_multicore_api.h"
#include "ciaa_gpio_api.h"

// Contador de interrupciones de M4
uint8_t m4_cnt = 0;

/**
 * @brief Callback para la interrupcion del M4
 */
void m4_callback(void) {
	// Conmuto cada dos interrupciones del M4
	if(m4_cnt++ == 1) {
		// Conmuto el LED2
		gpio_xor(LED2);
		// Interrumpo el M4
		multicore_interrupt_m4_core();
		// Limpio el contador
		m4_cnt = 0;
	}
}

/**
 * @brief Programa principal
 */
int main(void) {
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Configuro LED2 como salida
    gpio_set_dir_out(LED2);
    // Apago LED2
    gpio_clr(LED2);
    // Habilito interrupcion del M4
    multicore_m4_irq_set_enabled(true);

    while(1);

    return 0 ;
}

/**
 * @brief Handler de interrupcion del M4
 */
void M4_IRQHandler(void) {
	/* Clear interrupt */
	multicore_irq_clear();
	/* Call callback */
	m4_callback();
}
