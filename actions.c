/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:54:19 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/23 21:43:55 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(char c, t_philo *philo)
{
	long	i;

	pthread_mutex_lock(&philo->data->write);
	i = get_time() - philo->data->start_time;
	if (philo->data->dead)
		return 1;
	if (c == 'f')
	{
		printf("%ld Philo %i has taken a fork\n", i, philo->id);
		pthread_mutex_lock(&philo->l_fork);
		printf("%ld Philo %i has taken a fork\n", i, philo->id);
		pthread_mutex_lock(&philo->r_fork);
	}
	if (c == 'e')
		printf("Philo %i is eating\n", philo->id);
	if (c == 's')
		printf("Philo %i is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->data->write);
	return 0;
}

int	ft_sleep(t_philo *philo)
{
	if (print_status('s', philo))
		return 1;
	ft_usleep(philo->data->sleep_time);
	return 0;
}

int unlcokall(t_philo *philo, int o)
{
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->lock);
	return o;
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (print_status('f', philo))
		return unlcokall(philo, 1);
	philo->eating = 1;
	philo->eat_count++;
	if (print_status('e', philo))
		return unlcokall(philo, 1);
	ft_usleep(philo->data->eat_time);
	philo->time_to_die = get_time() + philo->data->death_time;
	philo->eating = 0;
	if (ft_sleep(philo))
		return unlcokall(philo, 1);
	return unlcokall(philo, 0);
}
