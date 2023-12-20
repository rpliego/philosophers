/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:48 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/20 14:37:30 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	printf("%i\n", philo->data->philo_nb);
	
	philo->time_to_die += get_time();
	printf("time->%ld\n", philo->time_to_die);
	//pthread_create(&philo->t1, NULL, &supervisor, &philo);
	while (philo->dead == 0)
	{
		eat(philo);
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
	}
	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_join(data->tid[i], NULL);
	}
}
