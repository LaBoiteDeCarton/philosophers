/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:56:41 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:56:43 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		put_error("bad number of argument");
	else
	{
		data = parse(ac - 1, av + 1);
		lunch_philosophers(&data);
	}
	return (EXIT_SUCCESS);
}
