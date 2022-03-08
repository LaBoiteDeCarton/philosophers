#include "philosophers.h"

static unsigned int	parse_value(char *str)
{
	if (!ft_strisui(str))
		put_error("bad argument");
	return (ft_atoui(str));
}

t_data parse(int ac, char **av)
{
	t_data data;

	data.n_of_phi = parse_value(av[0]);
	data.t_t_die = 1000 * parse_value(av[1]);
	data.t_t_eat = 1000 * parse_value(av[2]);
	data.t_t_sleep = 1000 * parse_value(av[3]);
	if (ac == 5)
	{
		data.end_if_die = 0;
		data.n_must_eat = parse_value(av[4]);
	}
	else
		data.end_if_die = 1;
	data.someone_died = FALSE;
	return (data);
}