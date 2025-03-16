#include <transfer.h>
#include <uart.h>
#include <common.h>
#include <exports.h>

int transfer_number_of_steps(int nb_steps)
{
	/* TODO: send number of step via UART */
	send_by_uart();
	return 0;
}

void receive_information(void)
{
	/* TODO: receive information via UART */
	receive_by_uart();
	return;
}
