#include "philosophers.h"

void	do_die(t_phi *phi)
{
	pthread_cancel(phi->th_id);
	put_message(phi, DIE_MSG);
	phi->isalive = FALSE;
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
	pthread_mutex_lock(phi->mx_fork_l);
	put_message(phi, FORK_MSG);
	pthread_mutex_lock(phi->mx_fork_r);
	put_message(phi, FORK_MSG);
	put_message(phi, EAT_MSG);
	usleep(phi->data->t_t_eat);
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
}