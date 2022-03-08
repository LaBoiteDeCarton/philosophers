#include "philosophers.h"

void	put_error(char *str)
{
	int n;

	n = ft_strlen(str);
	write(2, "ERROR: ", 7);
	write(2, str, n);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
