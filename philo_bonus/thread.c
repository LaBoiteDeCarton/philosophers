/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:33:03 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/15 17:33:06 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_imstarving(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		if (get_time(phi->last_meal) > phi->data->t_t_die)
		{
			sem_wait(phi->sem_stdoutaccess);
			if (!phi->stop)
			{
				printf("%010d    %-4d %s\n", get_time(phi->data->tstart),
					phi->id, DIE_MSG);
				sem_post(phi->sem_void);
				exit(EXIT_SUCCESS);
			}
		}
		ft_usleep(100);
	}
	return (NULL);
}
