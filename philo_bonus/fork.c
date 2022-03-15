/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:29:14 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/15 17:29:16 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sem_npost(sem_t *sem, int n)
{
	while (n-- > 0)
		sem_post(sem);
}

static void	set_threads(t_phi *phi)
{
	pthread_t	th_imstarving;

	pthread_create(&th_imstarving, NULL, &thread_imstarving, phi);
	pthread_detach(th_imstarving);
}

static void	phi_life(t_phi phi)
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

static void	do_wait_pid(pid_t *pid_idtab, int size)
{
	int	stat_loc;

	while (size-- > 0)
		waitpid(pid_idtab[size], &stat_loc, 0);
}

pid_t	fork_die(pid_t *pid_idtab, t_phi phi)
{
	pid_t			pid_iddie;
	unsigned int	i;

	pid_iddie = fork();
	if (pid_iddie == -1)
		put_error("unable to fork");
	else if (pid_iddie == 0)
	{
		sem_wait(phi.sem_void);
		i = 0;
		while (i < phi.data->n_phi)
			kill(pid_idtab[i++], SIGINT);
		exit(EXIT_SUCCESS);
	}
	return (pid_iddie);
}

void	fork_phi(t_phi phi)
{
	pid_t	*pid_idtab;
	pid_t	pid_iddie;

	pid_idtab = (pid_t *)malloc(sizeof(pid_t) * phi.data->n_phi + 1);
	if (!pid_idtab)
		put_error(MALLOC_ERR_MSG);
	while (++phi.id <= phi.data->n_phi)
	{
		pid_idtab[phi.id - 1] = fork();
		if (pid_idtab[phi.id -1] == -1)
			return ; // ici faire des kills ??
		else if (pid_idtab[phi.id -1] == 0)
		{
			free(pid_idtab);
			phi_life(phi);
			break ;
		}
	}
	pid_iddie = fork_die(pid_idtab, phi);
	sem_npost(phi.sem_start, phi.data->n_phi);
	do_wait_pid(pid_idtab, phi.data->n_phi);
	kill(pid_iddie, SIGINT);
	free(pid_idtab);
}
