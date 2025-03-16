#include <gpio.h>
#include <imu.h>
#include <ctrl_led.h>
#include <uart.h>
#include <system.h>
#include <common.h>
#include <exports.h>

void init_system(void)
{
	printf("[SYSTEM] Starting initialization...\n");
	init_uart();
	init_imu();
	init_leds();
	printf("[SYSTEM] End initialization!\n");

	return;
}

