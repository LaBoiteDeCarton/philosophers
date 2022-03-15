/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:22:13 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/15 12:22:16 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(struct timeval tstart)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec - tstart.tv_sec) * 1000000
		+ tval.tv_usec - tstart.tv_usec);
}
