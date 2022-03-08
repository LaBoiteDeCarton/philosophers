#include "philosophers.h"

void	do_die(t_phi *phi)
{
	pthread_cancel(phi->th_phi);
	put_message(phi, DIE_MSG);
	phi->data->someone_died = TRUE;
}

void	do_takerfork(t_phi *phi)
{
	pthread_mutex_lock(&(phi->data->mx_fork[phi->id % phi->data->n_of_phi]));
	put_message(phi, FORK_MSG);
}

void	do_takelfork(t_phi *phi)
{
	pthread_mutex_lock(&(phi->data->mx_fork[phi->id - 1]));
	put_message(phi, FORK_MSG);
}

void	do_think(t_phi *phi)
{
	put_message(phi, THINK_MSG);
}

void	do_sleep(t_phi *phi)
{
	put_message(phi, SLEEP_MSG);
	usleep(phi->data->t_t_sleep);
}

void	do_eat(t_phi *phi)
{
	put_message(phi, EAT_MSG);
	usleep(phi->data->t_t_eat);
	pthread_mutex_unlock(&(phi->data->mx_fork[phi->id % phi->data->n_of_phi]));
	pthread_mutex_unlock(&(phi->data->mx_fork[phi->id - 1]));
	gettimeofday(&phi->last_meal, NULL);
	phi->eat_count++;
}