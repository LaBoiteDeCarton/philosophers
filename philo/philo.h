/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:36:15 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/15 12:36:16 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define EAT_MSG "is eating"
# define FORK_MSG "has taken a fork"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"

typedef struct s_data	t_data;
typedef struct s_phi	t_phi;

struct s_data
{
	unsigned int	n_phi;
	unsigned int	t_t_eat;
	unsigned int	t_t_die;
	unsigned int	t_t_sleep;
	int				must_eat;
	int				phi_died;
	unsigned int	n_must_eat;
	struct timeval	tstart;
	pthread_mutex_t	mx_stdoutaccess;
};

struct	s_phi
{
	pthread_t		th_id;
	unsigned int	id;
	pthread_mutex_t	*mx_fork_l;
	pthread_mutex_t	*mx_fork_r;
	unsigned int	eat_count;
	struct timeval	last_meal;
	t_data			*data;
};

t_data			parse(int ac, char **av);
void			put_error(char *str);
void			put_message(t_phi *phi, char *str);

void			lunch_philo(t_data *data);
void			*thread_phi(void *arg);
void			*thread_starve(void *arg);

unsigned int	get_time(struct timeval tstart);

#endif
