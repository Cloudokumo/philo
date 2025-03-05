#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				nbr_eat;
    long	        last_meal;
	int				pos;
	char			*pos_str;
	int				lfork;
	int				rfork;
	struct s_data	*data;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_data
{
    int     count;
    int     t_death;
    int     t_eat;
    int     t_sleep;
    int     eat_max;
    t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
}           t_data;

#endif