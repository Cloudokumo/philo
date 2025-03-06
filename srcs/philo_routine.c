#include "philosophers.h"

void *ft_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->data->meal);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->data->meal);
    
    if (philo->pos % 2)
        ft_usleep(philo->data->t_eat / 2);
    
    while (!philo->data->stop)
    {
        ft_eat(philo);
        if (philo->data->eat_max > 0 && philo->nbr_eat >= philo->data->eat_max)
            break;
    }
    return (NULL);
}
int ft_start_threads(t_data *data)
{
    int i;
    pthread_t monitor;
    
    data->start_time = get_time();
    data->stop = 0;
    i = 0;
    while (i < data->count)
    {
        if (pthread_create(&data->philos[i].thread_id, NULL, ft_routine, &data->philos[i]))
            return (1);
        i++;
    }
    if (pthread_create(&monitor, NULL, ft_dead, data))
        return (1);
    if (pthread_detach(monitor))
        return (1);  
    ft_exit_threads(data);
    return (0);
}

void ft_exit_threads(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->count)
    {
        pthread_join(data->philos[i].thread_id, NULL);
        i++;
    }
    i = 0;
    while (i < data->count)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->meal);
    pthread_mutex_destroy(&data->print);
    i = 0;
    while (i < data->count)
    {
        free(data->philos[i].pos_str);
        i++;
    }
    free(data->philos);
    free(data->forks);
}
