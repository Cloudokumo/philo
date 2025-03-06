#include "philosophers.h"

int check_param(t_data *data, int argc, char *argv[])
{
    int     i;

    i = 0;
    while (i < argc)
    {
        if (!is_int(argv[i]))
            return (0);
        if (!ft_atoi(argv[i] < 0))
            return (0);
        i++;
    }
    if (argc == 6)
		data->eat_max = ft_atoi(argv[5]);
	else
		data->eat_max = 0;
    data->count = ft_atoi(argv[1]);
    data->t_death = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
    if (check_param_value(&data))
        return (0);
    return (1);
}
int check_param_value(t_data *data)
{
    if (data->count < 1 || data->t_death < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || data->eat_max < 0)
		return (0);
    return (1);
}

int main(int argc, char *argv[])
{
    t_data  data;

    if (argc < 5 || argc > 6)
        return (ft_write("incorrect number of arguments\n"), EXIT_FAILURE);
    if (!check_param(&data, argc, argv))
        return (ft_write("incorrect parameters\n"), EXIT_FAILURE);
    if (ft_init(&data) == EXIT_FAILURE)
        return (0);
    if (ft_start_threads(&data))
    {
        ft_write("Thread creation failed\n");
        ft_exit_threads(&data);
        return (EXIT_FAILURE);
    }
    return (0);
}
