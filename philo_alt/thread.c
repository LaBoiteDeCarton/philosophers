#include "philosophers.h"

unsigned int	time_beetween(struct timeval t_from, struct timeval t_to)
{
	unsigned int	res;

	res = (t_to.tv_sec - t_from.tv_sec) * 1000000;
	res += (t_to.tv_usec - t_from.tv_usec);
	return (res);
}

// static void check_someone_died(t_phi *phi)
// {
// 	if (phi->data->someone_died == TRUE)
// 		pthread_exit(EXIT_SUCCESS);
// }

void	*thread_dead(void *arg)
{
	t_phi	*phi;
	struct timeval	tval;
	unsigned int	interval;

	phi = (t_phi *)arg;
	usleep(phi->data->t_t_die);
	while (phi->data->someone_died == FALSE)
	{
		gettimeofday(&tval, NULL);
		interval = time_beetween(phi->last_meal, tval);
		if (interval > phi->data->t_t_die)
			do_die(phi);
		else
			usleep(phi->data->t_t_die - interval);
	}
	pthread_cancel(phi->th_phi);
	pthread_exit(EXIT_SUCCESS);
}

void	*thread_phi(void *arg) //thread_life
{
	t_phi		*phi;
	pthread_t	starve_thread;

	phi = (t_phi *)arg;
	phi->last_meal = phi->data->tstart;
	pthread_create(&starve_thread, NULL, &thread_dead, phi);
	pthread_detach(starve_thread);
	if (phi->id % 2)
		usleep(10);
	while (1)
	{
		do_takelfork(phi);
		do_takerfork(phi);
		do_eat(phi);
		if (phi->data->end_if_die == FALSE && phi->eat_count >= phi->data->n_must_eat)
			break ;
		do_sleep(phi);
		do_think(phi);
	}
	pthread_exit(EXIT_SUCCESS);
}