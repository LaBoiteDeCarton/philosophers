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

static void	retro_kill(pid_t *pid_idtab, int n)
{
	while (--n >= 0)
		kill(pid_idtab[n], SIGINT);
	free(pid_idtab);
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
		{
			retro_kill(pid_idtab, phi.id);
			return ;
		}
		else if (pid_idtab[phi.id -1] == 0)
		{
			free(pid_idtab);
			phi_life(phi);
		}
	}
	pid_iddie = fork_die(pid_idtab, phi);
	sem_npost(phi.sem_start, phi.data->n_phi);
	do_wait_pid(pid_idtab, phi.data->n_phi);
	kill(pid_iddie, SIGINT);
	free(pid_idtab);
}
