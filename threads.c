/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:48 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/23 21:39:41 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *data_pointer)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_pointer;
	i = 0;
	pthread_mutex_lock(&data->lock);
	while (data->dead == 0)
	{
		if (i == data->philo_nb)
			i = 0;
		//printf("time to die philo->%i -------> %ld\n", data->philos[i].id, data->philos[i].time_to_die);
		//printf("actual time------------------> %ld\n\n", get_time());
		if (data->philos[i].time_to_die <= get_time())
			data->dead = 1;
		if (data->dead == 1)
			printf("Philo %i has died\n", data->philos[i].id);
		if (data->dead == 1)
			break ;
		i++;
		pthread_mutex_unlock(&data->lock);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = get_time() + philo->data->death_time;
	while (philo->data->dead == 0) 
	{
		// if (philo->id % 2 == 0)
		// 	ft_usleep(philo->data->eat_time);
		if (eat(philo))
			break ;
		if (philo->eat_count == philo->data->meals_nb || philo->data->dead == 1)
			break ;
		printf("Philo %i is thinking\n", philo->id); //thinking TODO
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_nb)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
		ft_usleep(1);
	}
	pthread_create(&data->sp, NULL, &supervisor, data);
	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_join(data->tid[i], NULL);
	}
}
