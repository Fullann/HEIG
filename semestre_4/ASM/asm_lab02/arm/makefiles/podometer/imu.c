#include <imu.h>
#include <common.h>
#include <exports.h>

void init_imu(void)
{
	printf("[IMU] Starting initialization...\n");
	// Do things
	printf("[IMU] End initialization!\n");
	return;
}

int get_number_of_steps(int nb_steps)
{
	/* TODO: use gyroscope and accelerometer to count
	 *       the number of steps
	 */
	return 0;
}

void reset_nb_steps(void)
{
	/* TODO: reset number of steps */
	return;
}
