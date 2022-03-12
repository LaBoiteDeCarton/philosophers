#include "philo.h"

static void	sem_npost(sem_t *sem, int n)
{
	while (n-- > 0)
		sem_post(sem);
}

void	*thread_imstarving(void *arg)
{
	t_phi *phi;

	phi = (t_phi *)arg;
	while (!phi->stop)
	{
		if (get_time(phi->last_meal) > phi->data->t_t_die)
		{
			sem_wait(phi->sem_stdoutaccess);
			if (!phi->stop)
			{
				printf("%010d    %-4d %s\n", get_time(phi->data->tstart), phi->id, DIE_MSG);
				phi->stop = 1;
				sem_npost(phi->sem_void, phi->data->n_phi);
			}
			sem_post(phi->sem_stdoutaccess);
			
		}
		ft_usleep(100);
	}
	return (NULL);
}

void	*thread_otherlooser(void *arg)
{
	t_phi *phi;

	phi = (t_phi *)arg;
	sem_wait(phi->sem_void);
	phi->stop = 1;
	return (NULL);
}
