#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->pos % 2)
		ft_usleep(10);
	while (!philo->data->stop)
	{
		if (philo->data->eat_max && philo->nbr_eat >= philo->data->eat_max)
			break;
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

	data->start_time = get_time();
	i = 0;
	while (i < data->count)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL, 
				philo_routine, &data->philos[i]))
			return (1);
		i++;
	}
	while (!data->stop)
	{
		if (philo_dead(data))
			break;
		usleep(1000);
	}
	return (0);
}


void	ft_exit_threads(t_data *data)
{
	int	i;

	if (data->count == 1)
		pthread_detach(data->philos[0].thread_id);
	else
	{
		i = 0;
		while (i < data->count)
		{
			pthread_join(data->philos[i].thread_id, NULL);
			i++;
		}
	}
	
	i = 0;
	while (i < data->count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->print);
	
	free(data->philos);
	free(data->forks);
}
