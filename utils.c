/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:42:12 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/28 19:27:29 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	time += get_time();
	while (get_time() <= time)
		usleep(200);
}


// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }
