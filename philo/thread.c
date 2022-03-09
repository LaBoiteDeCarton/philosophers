#include "philosophers.h"

unsigned int	time_beetween(struct timeval t_from, struct timeval t_to)
{
	unsigned int	res;

	res = (t_to.tv_sec - t_from.tv_sec) * 1000000;
	res += (t_to.tv_usec - t_from.tv_usec);
	return (res);
}

void	ft_usleep(unsigned int time)
{
	struct timeval tstart;

	gettimeofday(&tstart, NULL);
	while (time > get_time(tstart))
		usleep(500);
}

void	*thread_dead(void *arg)
{
	t_phi	*phi;
	struct timeval	tval;
	unsigned int	interval;
	int		*phi_died;

	phi = (t_phi *)arg;
	phi_died = &(phi->data->phi_died);
	ft_usleep(phi->data->t_t_die);
	while (!*phi_died)
	{
		gettimeofday(&tval, NULL);
		interval = time_beetween(phi->last_meal, tval);
		if (phi->data->end_if_die == FALSE
			&& phi->eat_count >= phi->data->n_must_eat)
			break ;
		if (interval >= phi->data->t_t_die)
			die(phi);
		else
			ft_usleep(phi->data->t_t_die - interval);
	}
	return (NULL);
}

void launch_dead_checker(t_phi *phi)
{
	pthread_t	starve_thread;

	pthread_create(&starve_thread, NULL, &thread_dead, phi);
	pthread_detach(starve_thread);
}

static void	phi_life(t_phi *phi, int *phi_died)
{
	put_message(phi, THINK_MSG);
	pthread_mutex_lock(phi->mx_fork_l);
	if (*phi_died)
		return ;
	put_message(phi, FORK_MSG);
	pthread_mutex_lock(phi->mx_fork_r);
	if (*phi_died)
		return ;
	put_message(phi, FORK_MSG);
	gettimeofday(&phi->last_meal, NULL);
	put_message(phi, EAT_MSG);
	ft_usleep(phi->data->t_t_eat);
	phi->eat_count++;
	if (*phi_died)
		return ;
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
	if (phi->data->end_if_die == FALSE
			&& phi->eat_count >= phi->data->n_must_eat)
		return ;
	if (*phi_died)
		return ;
	put_message(phi, SLEEP_MSG);
	ft_usleep(phi->data->t_t_sleep);
}

void	*thread_phi(void *arg) //thread_life
{
	t_phi		*phi;
	int			*phi_died;

	phi = (t_phi *)arg;
	phi->last_meal = phi->data->tstart;
	phi_died = &phi->data->phi_died;
	launch_dead_checker(phi);
	if (phi->id % 2)
		ft_usleep(phi->data->t_t_eat / 2);
	while (!*phi_died)
	{
		if (phi->data->end_if_die == FALSE
			&& phi->eat_count >= phi->data->n_must_eat)
			break ;
		phi_life(phi, phi_died);
	}
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
	return (NULL);
}
