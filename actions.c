/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:54:19 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/28 19:43:44 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int status, t_philo *philo)
{
	long	i;

	if (philo->data->dead == 1 && status != DIED)
		return ;
	pthread_mutex_lock(&philo->data->write);
	i = get_time() - philo->data->start_time;
	// if (status == FORK_R)	
	// 	printf("%ld Philo %i has taken right fork\n", i, philo->id);
	if (status == FORK)	
		printf("%ld Philo %i has taken a fork\n", i, philo->id);
	if (status == EATING)
		printf("%ld Philo %i is eating\n", i, philo->id);
	if (status == SLEEP)
		printf("%ld Philo %i is sleeping\n", i, philo->id);
	if (status == THINK)
		printf("%ld Philo %i is thinking\n", i, philo->id);
	if (status == DIED)
		printf("%ld Philo %i has died\n", i, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status(FORK, philo);
	// print_status(FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	print_status(FORK, philo);
	// print_status(FORK, philo);
}

void	drop_fork(t_philo *philo)
{
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_status(SLEEP, philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	print_status(EATING, philo);
	philo->eating = 1;
	ft_usleep(philo->data->eat_time);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	drop_fork(philo);
}
