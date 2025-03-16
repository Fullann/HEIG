#include <gpio.h>
#include <ctrl_led.h>
#include <common.h>
#include <exports.h>

void init_leds(void)
{
	printf("[CTRL_LED] Starting initialization...\n");
	// Do things
	printf("[CTRL_LED] End initialization!\n");
	return;
}

void led_on(int led, int r, int g, int b)
{
	/* TODO: change the state of the GPIO corresponding to the LED */
	set_gpio();
	return;
}

void led_off(int led)
{
	/* TODO: change the state of the GPIO corresponding to the LED */
	set_gpio();
	return;
}
