#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	if (is_stopped(philo->data))
        return;
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
void lock_forks(t_philo *philo)
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
void unlock_forks(t_philo *philo)
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

void philo_print(t_philo *philo, char *message, int unlock)
{
    long timestamp;
 
    pthread_mutex_lock(&philo->data->print);
    if (!is_stopped(philo->data))
    {
        timestamp = get_time() - philo->data->start_time;
        printf("%ld %s %s\n", timestamp, philo->pos_str, message);
    }
    if (unlock)
        pthread_mutex_unlock(&philo->data->print);
}


int philo_dead(t_data *data)
{
    int     i;
    long    current_time;
    int     all_ate;
 
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
    if (data->eat_max && all_ate)
    {
        pthread_mutex_lock(&data->print);
        set_stop(data);
        pthread_mutex_unlock(&data->print);
        return (1);
    }
    return (0);
}


int ft_all_ate(t_data *data)
{
    int i;
    
    if (data->eat_max <= 0)
        return (0);
    i = 0;
    while (i < data->count)
    {
        pthread_mutex_lock(&data->meal);
        if (data->philos[i].nbr_eat < data->eat_max)
        {
            pthread_mutex_unlock(&data->meal);
            return (0);
        }
        pthread_mutex_unlock(&data->meal);
        i++;
    }
    return (1);
}
