#include "philosophers.h"

unsigned int	get_time(struct timeval tstart)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return((tval.tv_sec - tstart.tv_sec) * 1000000 + tval.tv_usec - tstart.tv_usec);
}

void	put_message(t_phi *phi, char *str)
{
	unsigned int	curr_time;

	pthread_mutex_lock(&(phi->data->mx_stdoutaccess));
	curr_time = get_time(phi->data->tstart);
	printf("%08d    %-4d %s\n", curr_time,phi->id, str);
	pthread_mutex_unlock(&(phi->data->mx_stdoutaccess));
}
