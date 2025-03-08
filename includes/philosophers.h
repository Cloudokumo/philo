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
	long 	start_time;
	int		stop;
    t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
}           t_data;

int 	check_param(t_data *data, int argc, char *argv[]);
int		ft_atoi(const char *nptr);
int		ft_write(char *str);
int		ft_strlen(char *str);
long	get_time(void);
int		is_int(const char *str);
int		ft_mutex(t_data *data);
int		ft_philo(t_data *data);
int		ft_init(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_print(t_philo *philo, char *message, int unlock);
int	philo_dead(t_data *data);
int 	ft_check_death(t_data *data, int *dead);
int 	ft_all_ate(t_data *data);
void	*philo_routine(void *arg);
int 	ft_start_threads(t_data *data);
void 	ft_usleep(long time);
void 	ft_exit_threads(t_data *data);
int	ft_isdigit(int c);
void	ft_reverse_str(char *str);
char	*ft_itoa(int n);
int	ft_getlen(int n);

#endif