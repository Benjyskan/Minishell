#include "tuto.h"

void	mem_error(void)
{
	write(2, "Mermory error\n", 15);
	exit(EXIT_FAILURE);
}
