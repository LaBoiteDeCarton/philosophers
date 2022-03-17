/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:30:24 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/15 17:30:29 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned int time)
{
	struct timeval	tstart;

	gettimeofday(&tstart, NULL);
	while (time > get_time(tstart))
		usleep(100);
}
