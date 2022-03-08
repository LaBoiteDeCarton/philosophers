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
	t_bool			isalive;
	t_times			*data;
};

t_times 		parse(int ac, char **av);
void			put_error(char *str);
void			put_message(t_phi *phi, char *str);
unsigned int	ft_atoui(const char *str);
int				ft_strisui(char *str);
int				ft_isdigit(char c);
size_t			ft_strlen(const char *s);

void			lunch_philosophers(t_times data);
void			*thread_phi(void *arg);

void			do_die(t_phi *phi);
void			do_think(t_phi *phi);
void			do_eat(t_phi *phi);
void			do_sleep(t_phi *phi);
unsigned int	get_time(struct timeval tstart);

#endif