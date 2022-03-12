#include "philo.h"

static void	set_threads(t_phi *phi)
{
	pthread_t	th_imstarving;
	pthread_t	th_otherlooser;

	pthread_create(&th_imstarving, NULL, &thread_imstarving, phi);
	pthread_create(&th_otherlooser, NULL, &thread_otherlooser, phi);
	pthread_detach(th_imstarving);
	pthread_detach(th_otherlooser);
}

static void	phi_life(t_phi phi)
{
	phi.last_meal = phi.data->tstart;
	set_threads(&phi);
	while (!phi.stop)
	{
		sem_wait(phi.sem_fork);
		put_message(&phi, FORK_MSG);
		sem_wait(phi.sem_fork);
		put_message(&phi, FORK_MSG);
		put_message(&phi, EAT_MSG);
		gettimeofday(&(phi.last_meal), NULL);
		ft_usleep(phi.data->t_t_eat);
		phi.eat_count++;
		sem_post(phi.sem_fork);
		sem_post(phi.sem_fork);
		if (phi.data->must_eat && phi.eat_count >= phi.data->n_must_eat)
		{
			sem_post(phi.sem_void);
			phi.stop = 1;
		}
		put_message(&phi, SLEEP_MSG);
		ft_usleep(phi.data->t_t_sleep);
		put_message(&phi, THINK_MSG);
	}
	exit(EXIT_SUCCESS);
}

void	fork_phi(t_phi phi)
{
	pid_t	pid_id;
	int		stat_loc;

	phi.id++;
	if (phi.id > phi.data->n_phi)
		return ;
	pid_id = fork();
	if (pid_id == -1)
		put_error("unable to fork"); //quoi faire?
	if (pid_id == 0)
		phi_life(phi);
	else 
	{
		fork_phi(phi);
		waitpid(0, &stat_loc, 0);
	}
}