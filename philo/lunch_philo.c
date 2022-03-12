/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:56:36 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:56:37 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_phi_thread(t_phi *phi, pthread_mutex_t *fork, t_data*data)
{
	int	i;

	i = 0;
	while (i < (int)data->n_phi)
	{
		phi[i].id = i + 1;
		phi[i].data = data;
		phi[i].mx_fork_l = &fork[i];
		phi[i].mx_fork_r = &fork[i + 1 % data->n_phi];
		phi[i].eat_count = 0;
		i++;
	}
	i = 0;
	gettimeofday(&data->tstart, NULL);
	while (i < (int)data->n_phi)
	{
		phi[i].last_meal = phi->data->tstart;
		pthread_create(&phi[i].th_id, NULL, &thread_phi, &phi[i]);
		i++;
	}
}

static void	mutex_free(pthread_mutex_t *mx_tab, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mx_tab[i++]);
}

void	lunch_philo(t_data *data)
{
	int				i;
	t_phi			*phi;
	pthread_mutex_t	*mx_fork;
	pthread_t		th_starver;

	phi = (t_phi *)malloc(sizeof(t_phi) * data->n_phi);
	if (!phi)
		put_error("unable to malloc");
	mx_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_phi);
	if (!mx_fork)
	{
		free(phi);
		put_error("unable to malloc");
	}
	i = 0;
	while (i < (int)data->n_phi)
		pthread_mutex_init(&mx_fork[i++], NULL);
	pthread_mutex_init(&(data->mx_stdoutaccess), NULL);
	set_phi_thread(phi, mx_fork, data);
	pthread_create(&th_starver, NULL, &thread_starve, phi);
	i = 0;
	while (i < (int)data->n_phi)
		pthread_join(phi[i++].th_id, NULL);
	mutex_free(mx_fork, phi->data->n_phi);
}
