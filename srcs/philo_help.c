/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiehl-b <adiehl-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:11:59 by adiehl-b          #+#    #+#             */
/*   Updated: 2025/03/13 16:12:00 by adiehl-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	if (is_stopped(philo->data))
		return ;
	lock_forks(philo);
	philo_print(philo, "has taken a fork", 1);
	philo_print(philo, "has taken a fork", 1);
	philo_print(philo, "is eating", 1);
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_time();
	philo->nbr_eat++;
	pthread_mutex_unlock(&philo->data->meal);
	ft_usleep(philo->data->t_eat);
	unlock_forks(philo);
}

void	lock_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	}
}

int	philo_dead(t_data *data)
{
	int		i;
	long	current_time;
	int		all_ate;

	i = 0;
	all_ate = 1;
	while (i < data->count)
	{
		pthread_mutex_lock(&data->meal);
		current_time = get_time();
		if (current_time - data->philos[i].last_meal > data->t_death)
		{
			pthread_mutex_unlock(&data->meal);
			philo_print(&data->philos[i], "died", 0);
			set_stop(data);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		if (data->eat_max && data->philos[i].nbr_eat < data->eat_max)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal);
		i++;
	}
	return (all_philos_ate(data, all_ate));
}

int	all_philos_ate(t_data *data, int all_ate)
{
	if (data->eat_max && all_ate)
	{
		pthread_mutex_lock(&data->print);
		set_stop(data);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}
