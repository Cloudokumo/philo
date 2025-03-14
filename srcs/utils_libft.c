/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiehl-b <adiehl-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:12:18 by adiehl-b          #+#    #+#             */
/*   Updated: 2025/03/13 16:12:19 by adiehl-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+') && nptr[i])
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] && (ft_isdigit(nptr[i]) == 1))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_reverse_str(char *str)
{
	int		begin;
	int		end;
	char	temp;

	begin = 0;
	end = ft_strlen(str) - 1;
	while (begin < end)
	{
		temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;
		begin++;
		end--;
	}
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				i;
	unsigned int	tmp_nbr;

	i = 0;
	ret = malloc(sizeof(*ret) * (ft_getlen(n) + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
		tmp_nbr = -1 * n;
	else
		tmp_nbr = n;
	while (tmp_nbr != 0)
	{
		ret[i++] = (tmp_nbr % 10) + '0';
		tmp_nbr /= 10;
	}
	if (n == 0)
		ret[i++] = '0';
	if (n < 0)
		ret[i++] = '-';
	ret[i] = '\0';
	ft_reverse_str(ret);
	return (ret);
}
