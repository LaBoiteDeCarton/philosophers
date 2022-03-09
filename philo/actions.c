#include "philosophers.h"

void	die(t_phi *phi)
{
	phi->data->phi_died = 1;
	put_message(phi, DIE_MSG);
}

void	sleeping(t_phi *phi, int *phi_died)
{
	if (*phi_died)
		return ;
	put_message(phi, SLEEP_MSG);
	usleep(phi->data->t_t_sleep);
}

void	take_forks(t_phi *phi, int *phi_died)
{
	pthread_mutex_lock(phi->mx_fork_l);
	if (*phi_died)
		return ;
	put_message(phi, FORK_MSG);
	pthread_mutex_lock(phi->mx_fork_r);
	if (*phi_died)
		return ;
	put_message(phi, FORK_MSG);
}

void	eat(t_phi *phi, int *phi_died)
{
	gettimeofday(&phi->last_meal, NULL);
	put_message(phi, EAT_MSG);
	usleep(phi->data->t_t_eat);
	phi->eat_count++;
	if (*phi_died)
		return ;
	pthread_mutex_unlock(phi->mx_fork_l);
	pthread_mutex_unlock(phi->mx_fork_r);
}