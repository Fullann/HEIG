#include <gpio.h>
#include <uart.h>
#include <common.h>
#include <exports.h>

void init_uart(void)
{
	/* TODO: program the TX and RX GPIOs */
	printf("[UART] Starting initialization...\n");
	// Do things
	init_gpios();
	printf("[UART] End initialization!\n");
	return;
}

void send_by_uart(void)
{
	/* TODO: use the GPIO to send data */
	return;
}

void receive_by_uart(void)
{
	/* TODO: use the GPIO to receive data */
	return;
}
