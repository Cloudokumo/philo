#include "philosophers.h"

long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void ft_write(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    write(2, str, i);
}


int	is_int(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > 214748364 || (res == 214748364 && 
			((sign == 1 && str[i] - '0' > 7) || 
			 (sign == -1 && str[i] - '0' > 8))))
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}

void ft_usleep(long time)
{
    long start;
    
    start = get_time();
    while (get_time() - start < time)
        usleep(100);
}