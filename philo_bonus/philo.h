/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:56:52 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:56:53 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# define EAT_MSG "is eating"
# define FORK_MSG "has taken a fork"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIE_MSG "died"
# define SEM_ERR_MSG "Semaphore could not be opened for a reason"
# define MALLOC_ERR_MSG "Unable to malloc something important"

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
};

struct	s_phi
{
	unsigned int	id;
	unsigned int	eat_count;
	int				stop;
	sem_t			*sem_fork;
	sem_t			*sem_void;
	sem_t			*sem_stdoutaccess;
	sem_t			*sem_start;
	struct timeval	last_meal;
	t_data			*data;
};

t_data			parse(int ac, char **av);
void			put_error(char *str);
void			put_message(t_phi *phi, char *str);

void			lunch_philo(t_data *data);
void			fork_phi(t_phi phi);
void			*thread_imstarving(void *arg);
void			*thread_otherlooser(void *arg);
void			phi_life(t_phi phi);

unsigned int	get_time(struct timeval tstart);
void			ft_usleep(unsigned int time);

#endif
