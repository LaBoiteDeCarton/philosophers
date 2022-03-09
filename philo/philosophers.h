#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
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

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

struct s_data
{
	unsigned int	n_of_phi;
	unsigned int	t_t_eat;
	unsigned int	t_t_die;
	unsigned int	t_t_sleep;
	t_bool			end_if_die;
	int				phi_died;
	unsigned int	n_must_eat;
	struct timeval 	tstart;
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

t_data 			parse(int ac, char **av);
void			put_error(char *str);
void			put_message(t_phi *phi, char *str);

void			lunch_philosophers(t_data *data);
void			*thread_phi(void *arg);

void			die(t_phi *phi);
void			take_forks(t_phi *phi, int *phi_died);
void			eat(t_phi *phi, int *phi_died);
void			sleeping(t_phi *phi, int *phi_died);
unsigned int	get_time(struct timeval tstart);
void			ft_usleep(unsigned int time);

#endif