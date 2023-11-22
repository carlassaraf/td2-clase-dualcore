/*
===============================================================================
 Name        : ciaa_multicore_ejemplo_02_m4.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ciaa_multicore_api.h"
#include "ciaa_gpio_api.h"
#include "ciaa_stdlib.h"

// Contador de interrupciones de systick
uint16_t systick_cnt = 0;
// Contador de interrupciones de M0
uint8_t m0_cnt = 0;

/**
 * @brief Callback para la interrupcion del M0
 */
void m0app_callback(void) {
	// Conmuto cada dos interrupciones del M0
	if(m0_cnt++ == 1) {
		// Conmuto LED3
		gpio_xor(LED3);
		// Reseteo contador
		m0_cnt = 0;
	}
}


/**
 * @brief Programa principal
 */
int main(void) {
	// Clock del sistema
	SystemCoreClockUpdate();
	// Configuro los LEDs 1 y 3 como salidas
	gpio_set_dir_out(LED1);
	gpio_set_dir_out(LED3);
	// Arranco el M0
	multicore_m0_start();
	// Habilito interrupcion por M0
	multicore_m0app_irq_set_enabled(true);
	// Apago los LEDs 1 y 3
	gpio_clr(LED1);
	gpio_clr(LED3);
	// Configuro el systick para 1 ms
	SysTick_Config(SystemCoreClock / 1000);

	while (1);

}

/**
 * @brief Handler para la interrupcion de SysTick
 */
void SysTick_Handler(void) {
	// Verifico que hayan pasado 500 ms
	if(systick_cnt++ == 500) {
		// Conmuto el LED3
		gpio_xor(LED1);
		// Reinicio contador
		systick_cnt = 0;
		// Interrumpo el M0
		multicore_interrupt_m0_core();
	}
}


/**
 * @brief Handler para la interrupcion que viene del M0
 */
void M0APP_IRQHandler(void) {
	/* Clear interrupt */
	multicore_irq_clear();
	/* Call callback */
	m0app_callback();
}

