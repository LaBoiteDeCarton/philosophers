/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:56:47 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:56:48 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static unsigned int	ft_atoui(const char *str)
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

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_strisui(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static unsigned int	parse_value(char *str)
{
	if (!ft_strisui(str))
		put_error("bad argument");
	return (ft_atoui(str));
}

t_data	parse(int ac, char **av)
{
	t_data	data;

	data.n_phi = parse_value(av[0]);
	data.t_t_die = 1000 * parse_value(av[1]);
	data.t_t_eat = 1000 * parse_value(av[2]);
	data.t_t_sleep = 1000 * parse_value(av[3]);
	data.phi_died = 0;
	if (ac == 5)
	{
		data.must_eat = 1;
		data.n_must_eat = parse_value(av[4]);
	}
	else
		data.must_eat = 0;
	return (data);
}
