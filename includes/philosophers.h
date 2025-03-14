/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiehl-b <adiehl-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:12:41 by adiehl-b          #+#    #+#             */
/*   Updated: 2025/03/13 16:12:42 by adiehl-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				nbr_eat;
	long			last_meal;
	int				pos;
	char			*pos_str;
	int				lfork;
	int				rfork;
	struct s_data	*data;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_data
{
	int				count;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				eat_max;
	long			start_time;
	int				stop;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print;
}					t_data;

int					check_param(t_data *data, int argc, char *argv[]);
int					ft_atoi(const char *nptr);
void				ft_write(char *str);
int					ft_strlen(char *str);
long				get_time(void);
int					is_int(const char *str);
int					ft_mutex(t_data *data);
int					ft_philo(t_data *data);
int					ft_philo_help(t_data *data, int i);
int					all_philos_ate(t_data *data, int all_ate);
int					ft_init(t_data *data);
void				philo_eat(t_philo *philo);
void				philo_print(t_philo *philo, char *message, int unlock);
int					philo_dead(t_data *data);
void				*philo_routine(void *arg);
int					ft_start_threads(t_data *data);
void				ft_usleep(long time);
void				clean(t_data *data);
int					ft_isdigit(int c);
void				ft_reverse_str(char *str);
char				*ft_itoa(int n);
int					ft_getlen(int n);
void				set_stop(t_data *data);
int					is_stopped(t_data *data);
void				lock_forks(t_philo *philo);
void				unlock_forks(t_philo *philo);
void				one_philo(t_data *data);

#endif