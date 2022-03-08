#include "philosophers.h"

unsigned int	ft_atoui(const char *str)
{
	long	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > UINT32_MAX)
			return (UINT32_MAX);
	}
	return ((unsigned int)res);
}