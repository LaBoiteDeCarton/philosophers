#include "philosophers.h"

static void	set_phi_thread(t_phi *phi, pthread_mutex_t *fork, t_data*data)
{
	int i;

	i = 0;
	while (i < (int)data->n_of_phi)
	{
		phi[i].id = i + 1;
		phi[i].data = data;
		phi[i].isalive = TRUE;
		phi[i].mx_fork_l = &fork[i];
		phi[i].mx_fork_r = &fork[i + 1 % data->n_of_phi];
		phi[i].eat_count = 0;
		i++;
	}
	i = 0;
	gettimeofday(&data->tstart, NULL);
	while (i < (int)data->n_of_phi)
	{
		pthread_create(&phi[i].th_id, NULL, &thread_phi, &phi[i]);
		i++;
	}
}

void	lunch_philosophers(t_data data)
{
	int	i;
	t_phi			*phi;
	pthread_mutex_t	*mx_fork;

	phi = (t_phi *)malloc(sizeof(t_phi) * data.n_of_phi);
	if (!phi)
		put_error("unable to malloc");
	mx_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.n_of_phi);
	if (!mx_fork)
	{
		free(phi);
		put_error("unable to malloc");
	}
	i = 0;
	while (i < (int)data.n_of_phi)
		pthread_mutex_init(&mx_fork[i++], NULL);
	set_phi_thread(phi, mx_fork, &data);
	i = 0;
	while (i < (int)data.n_of_phi)
		pthread_join(phi[i++].th_id, NULL);
	pthread_mutex_destroy(fork);
}