#include "philosophers.h"

int	ft_write(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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