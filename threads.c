/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:48 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/28 19:42:16 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *data_pointer)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_pointer;
	i = 0;
	//ft_usleep(data->death_time - (data->death_time / 4));
	while (data->dead == 0)
	{
		if (i == data->philo_nb)
			i = 0;
		if (data->philos[i].time_to_die <= get_time() && data->philos[i].eating == 0
				&& data->philos[i].finished == 0)
			data->dead = 1;
		if (data->dead == 1)
			print_status(DIED, &data->philos[i]);
		if (data->dead == 1)
			break ;
		if (data->philos[i].finished == 1)
			break ;
		i++;
	}
	// if (data->dead == 1)
	// 	ft_exit(data);
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = get_time() + philo->data->death_time;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time);
	while (philo->data->dead == 0) 
	{
		eat(philo);
		if (philo->eat_count == philo->data->meals_nb)
		{
			philo->finished = 1;
			break ;
		}
		print_status(THINK, philo);
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
		pthread_join(data->tid[i], NULL);
	pthread_join(data->sp, NULL);
}
