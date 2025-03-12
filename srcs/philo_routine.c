#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->pos % 2)
		ft_usleep(10);
	while (!is_stopped(philo->data))
	{
		if (philo->data->eat_max && philo->nbr_eat >= philo->data->eat_max)
			break ;
		philo_eat(philo);
		philo_print(philo, "is sleeping", 1);
		ft_usleep(philo->data->t_sleep);
		philo_print(philo, "is thinking", 1);
		usleep(100);
	}
	return (NULL);
}

int	ft_start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	while (!is_stopped(data))
	{
		if (philo_dead(data))
			break ;
	}
	i = 0;
	while (i < data->count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		free(data->philos[i].pos_str);
		i++;
	}
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philos);
	free(data->forks);
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stopped);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
