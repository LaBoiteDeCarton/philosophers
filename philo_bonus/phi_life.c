/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:33:24 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/18 11:33:26 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_threads(t_phi *phi)
{
	pthread_t	th_imstarving;

	pthread_create(&th_imstarving, NULL, &thread_imstarving, phi);
	pthread_detach(th_imstarving);
}

void	phi_life(t_phi phi)
{
	phi.last_meal = phi.data->tstart;
	sem_wait(phi.sem_start);
	set_threads(&phi);
	if (phi.id % 2)
		usleep(phi.data->t_t_eat / 2);
	while (!phi.stop)
	{
		sem_wait(phi.sem_fork);
		put_message(&phi, FORK_MSG);
		sem_wait(phi.sem_fork);
		put_message(&phi, FORK_MSG);
		put_message(&phi, EAT_MSG);
		gettimeofday(&(phi.last_meal), NULL);
		ft_usleep(phi.data->t_t_eat);
		phi.eat_count++;
		sem_post(phi.sem_fork);
		sem_post(phi.sem_fork);
		if (phi.data->must_eat && phi.eat_count >= phi.data->n_must_eat)
			phi.stop = 1;
		put_message(&phi, SLEEP_MSG);
		ft_usleep(phi.data->t_t_sleep);
		put_message(&phi, THINK_MSG);
	}
	exit(EXIT_SUCCESS);
}
