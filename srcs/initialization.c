#include "philosophers.h"

int	ft_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (1);
	return (0);
}

int	ft_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		data->start_time = get_time();
		data->philos[i].nbr_eat = 0;
		data->philos[i].pos = i + 1;
		data->philos[i].pos_str = ft_itoa(i + 1);
		if (!data->philos[i].pos_str)
			break ;
		data->philos[i].rfork = i;
		data->philos[i].lfork = (i + 1) % data->count;
		data->philos[i].data = data;
		i++;
	}
	if (data->count == 1)
	{
		one_philo(data);
		return (EXIT_FAILURE);
	}
	if (i != data->count)
	{
		while (i >= 0)
		{
			free(data->philos[i].pos_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_init(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->count);
	if (!data->philos)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count);
	if (!data->forks)
	{
		free(data->philos);
		return (0);
	}
	if (ft_mutex(data))
	{
		free(data->philos);
		free(data->forks);
		return (0);
	}
	if (ft_philo(data))
	{
		free(data->philos);
		free(data->forks);
		return (0);
	}
	return (1);
}
