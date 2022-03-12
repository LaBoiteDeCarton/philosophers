#include "philo.h"

void	ft_usleep(unsigned int time)
{
	struct timeval	tstart;

	gettimeofday(&tstart, NULL);
	while (time > get_time(tstart))
		usleep(100);
}