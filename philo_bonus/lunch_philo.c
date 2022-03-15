/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:56:36 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:56:37 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_default_phi(t_phi *phi, t_data *data)
{
	phi->eat_count = 0;
	phi->data = data;
	phi->id = 0;
	phi->stop = 0;
}

static void	sem_unlink_all(void)
{
	sem_unlink("/forks");
	sem_unlink("/killme");
	sem_unlink("/stdoutaccess");
	sem_unlink("/start");
}

void	lunch_philo(t_data *data)
{
	t_phi	phi;

	sem_unlink_all();
	phi.sem_fork = sem_open("/forks", O_CREAT, S_IRWXU, data->n_phi);
	phi.sem_void = sem_open("/killme", O_CREAT, S_IRWXU, 0);
	phi.sem_stdoutaccess = sem_open("/stdoutaccess", O_CREAT, S_IRWXU, 1);
	phi.sem_start = sem_open("/start", O_CREAT, S_IRWXU, 0);
	if (phi.sem_void == SEM_FAILED || phi.sem_fork == SEM_FAILED
		|| phi.sem_stdoutaccess == SEM_FAILED)
	{
		sem_unlink_all();
		put_error(SEM_ERR_MSG);
	}
	gettimeofday(&data->tstart, NULL);
	set_default_phi(&phi, data);
	fork_phi(phi);
	sem_unlink_all();
}
