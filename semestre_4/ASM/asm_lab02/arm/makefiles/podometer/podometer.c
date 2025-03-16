#include <imu.h>
#include <ctrl_led.h>
#include <system.h>
#include <transfer.h>
#include <common.h>
#include <exports.h>

int main(int argc, char *argv[])
{
	int status;
	int nb_steps;
        
	init_system();

	
	status = get_number_of_steps(nb_steps);
	if (status < 0)
		led_on(LED1, 1, 0, 0);

	status = transfer_number_of_steps(nb_steps);
	if (status < 0)
		led_on(LED1, 1, 0, 0);

	return 0;
}
