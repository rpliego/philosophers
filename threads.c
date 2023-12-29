/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:48 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/29 21:28:18 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	*ft_aux(t_data *data, int i)
{
	long	*out;
	
	pthread_mutex_lock(&data->philos[i].lock);
	out[0] = data->philos[i].time_to_die;
	pthread_mutex_unlock(&data->philos[i].lock);
	out[1] = data->philos[i].finished;
	pthread_mutex_lock(&data->philos[i].lock);
	out[2] = data->philos[i].eating;
	
	return(out);
}

void	*supervisor(void *data_pointer)
{
	t_data	*data;
	int		i;
	long	aux[3];

	data = (t_data *)data_pointer;
	i = 0;
	while (data->dead == 0)
	{
		aux = ft_aux(data, i);
		if (aux[0] <= get_time() && aux[1] == 0 && aux[2] == 0)
		{
			pthread_mutex_lock(&data->lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->lock);
			print_status(DIED, &data->philos[i]);
		}
		i++;
		if (data->philos[i].finished == 1)
			break ;
		if (i == data->philo_nb)
			i = 0;
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time / 10);
	while (1) 
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->dead != 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
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
