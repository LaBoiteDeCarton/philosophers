#include "philosophers.h"
#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
void	put_error(char *str)
{
	int n;

	n = ft_strlen(str);
	write(2, "ERROR: ", 7);
	write(2, str, n);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
