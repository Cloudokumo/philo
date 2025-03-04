#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int     count;
    int     t_death;
    int     t_eat;
    int     t_sleep;
    int     eat_max;
}           t_data;

#endif