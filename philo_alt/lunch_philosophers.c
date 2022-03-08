#include "philosophers.h"

static void	set_phi_thread(t_phi *phi, t_data *data)
{
	int i;

	i = 0;
	while (i < (int)data->n_of_phi)
	{
		phi[i].id = i + 1;
		phi[i].data = data;
		phi[i].eat_count = 0;
		i++;
	}
	i = 0;
	gettimeofday(&data->tstart, NULL);
	while (i < (int)data->n_of_phi)
	{
		pthread_create(&(phi[i].th_phi), NULL, &thread_phi, &phi[i]);
		i++;
	}
}

void	lunch_philosophers(t_data *data)
{
	int	i;
	t_phi	*phi;

	phi = (t_phi *)malloc(sizeof(t_phi) * data->n_of_phi);
	if (!phi)
		put_error("unable to malloc");
	data->mx_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_of_phi);
	if (!data->mx_fork)
	{
		free(phi);
		put_error("unable to malloc");
	}
	i = 0;
	while (i < (int)data->n_of_phi)
		pthread_mutex_init(&data->mx_fork[i++], NULL);
	set_phi_thread(phi, data);
	i = 0;
	while (i < (int)data->n_of_phi)
		pthread_join(phi[i++].th_phi, NULL);
	pthread_mutex_destroy(data->mx_fork); // faire une boucle sur i ?
}