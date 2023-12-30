/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:54:19 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/30 20:32:19 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int status, t_philo *philo)
{
	long	i;

	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_lock(&philo->lock);
	i = get_time() - philo->data->start_time;
	if (status == FORK && philo->data->dead != 1)
		printf("%s%ld Philo %i has taken a fork\n%s", G, i, philo->id, E);
	if (status == EATING && philo->data->dead != 1)
		printf("%s%ld Philo %i is eating\n%s", Y, i, philo->id, E);
	if (status == SLEEP && philo->data->dead != 1)
		printf("%s%ld Philo %i is sleeping\n%s", C, i, philo->id, E);
	if (status == THINK && philo->data->dead != 1)
		printf("%s%ld Philo %i is thinking\n%s", O, i, philo->id, E);
	if (status == DIED)
		printf("%s%ld Philo %i has died\n%s", R, i, philo->id, E);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	print_status(FORK, philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->finished != 1)
	{
		print_status(SLEEP, philo);
		ft_usleep(philo->data->sleep_time);
	}
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	print_status(EATING, philo);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->eat_count == philo->data->meals_nb)
	{
		philo->finished = 1;
		philo->data->finish_all++;
	}
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo->data->eat_time);
	drop_fork(philo);
}
