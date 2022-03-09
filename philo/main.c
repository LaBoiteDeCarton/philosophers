#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data data;

	ft_usleep(30);
	if (ac < 5 || ac > 6)
		put_error("bad number of argument");
	else
	{
		data = parse(ac - 1, av + 1);
		lunch_philosophers(&data);
	}
	return (EXIT_SUCCESS);
}