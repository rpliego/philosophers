/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:27:47 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/02 17:38:43 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	out;

	out = 0;
	while (*str != '\0')
	{
		out = out * 10 + *str - '0';
		str++;
	}
	return (out);
}

int	ft_isvalid(char *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	ft_isnumber(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < 5)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Try 4 or 5 arguments\n"));
	if (ft_isnumber(av) != 0)
		return (printf("Try valid numbers\n"));
	if (ac == 6)
	{
		if (ft_isvalid(av[5]) != 0)
			return (printf("Try a valid number\n"));
	}
	if (ft_atoi(av[1]) > 200)
		return (printf("Max 200 Philosophers\n"));
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[2]) == 0
		|| ft_atoi(av[3]) == 0 || ft_atoi(av[4]) == 0)
		return (printf("First 4 argmuments must be bigger than 0\n"));
	return (0);
}
