/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:57:10 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:57:11 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(unsigned int time, t_phi *phi)
{
	struct timeval	tstart;

	gettimeofday(&tstart, NULL);
	while (time > get_time(tstart) && !phi->data->phi_died)
		usleep(1000);
}

static void	phi_die(t_phi *phi)
{
	pthread_mutex_lock(&(phi->data->mx_stdoutaccess));
	if (!phi->data->phi_died)
	{
		printf("%010d    %-4d %s\n", get_time(phi->data->tstart),
			phi->id, DIE_MSG);
		phi->data->phi_died = 1;
	}
	pthread_mutex_unlock(&(phi->data->mx_stdoutaccess));
}

void	*thread_starve(void *arg)
{
	unsigned int	i;
	t_phi			*phi;

	phi = (t_phi *)arg;
	while (!phi->data->phi_died)
	{
		i = 0;
		while (i < phi->data->n_phi)
		{
			if (get_time(phi->last_meal) >= phi->data->t_t_die)
				phi_die(&phi[i]);
			i++;
		}
	}
	return (NULL);
}

static void	phi_life(t_phi *phi)
{
	pthread_mutex_lock(phi->mx_fork_l);
	put_message(phi, FORK_MSG);
	pthread_mutex_lock(phi->mx_fork_r);
	put_message(phi, FORK_MSG);
	gettimeofday(&phi->last_meal, NULL);
	put_message(phi, EAT_MSG);
	ft_usleep(phi->data->t_t_eat, phi);
	phi->eat_count++;
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
	if (phi->data->must_eat && phi->eat_count >= phi->data->n_must_eat)
		return ;
	put_message(phi, SLEEP_MSG);
	ft_usleep(phi->data->t_t_sleep, phi);
	put_message(phi, THINK_MSG);
}

void	*thread_phi(void *arg)
{
	t_phi		*phi;

	phi = (t_phi *)arg;
	if (phi->data->n_phi == 1)
	{
		pthread_mutex_lock(phi->mx_fork_l);
		put_message(phi, FORK_MSG);
		ft_usleep(phi->data->t_t_die);
		return (NULL);
	}
	if (phi->id % 2)
		usleep(phi->data->t_t_eat / 2);
	while (!phi->data->phi_died && !(phi->data->must_eat && phi->eat_count >= phi->data->n_must_eat))
		phi_life(phi);
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
	return (NULL);
}
