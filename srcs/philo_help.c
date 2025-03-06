#include "philosophers.h"

void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->rfork]);
    ft_print(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[philo->lfork]);
    ft_print(philo, "has taken a fork");
    
    pthread_mutex_lock(&philo->data->meal);
    philo->last_meal = get_time();
    ft_print(philo, "is eating");
    philo->nbr_eat++;
    pthread_mutex_unlock(&philo->data->meal);
    
    ft_usleep(philo->data->t_eat);
    
    pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
    pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
    
    ft_print(philo, "is sleeping");
    ft_usleep(philo->data->t_sleep);
    
    ft_print(philo, "is thinking");
}
void ft_print(t_philo *philo, char *str)
{
    long time;
    
    time = get_time() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print);
    if (!philo->data->stop)
        printf("%ld %d %s\n", time, philo->pos, str);
    pthread_mutex_unlock(&philo->data->print);
}
void *ft_dead(void *arg)
{
    t_data *data;
    int dead;
    
    data = (t_data *)arg;
    dead = 0;
    while (!dead)
    {
        if (ft_check_death(data, &dead) || ft_all_ate(data))
            break;
        usleep(1000);
    }
    return (NULL);
}

int ft_check_death(t_data *data, int *dead)
{
    int i;
    long current_time;
    
    i = 0;
    while (i < data->count)
    {
        current_time = get_time();
        pthread_mutex_lock(&data->meal);
        if (current_time - data->philos[i].last_meal >= data->t_death)
        {
            pthread_mutex_unlock(&data->meal);
            ft_print(&data->philos[i], "died");
            *dead = 1;
            return (1);
        }
        pthread_mutex_unlock(&data->meal);
        i++;
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