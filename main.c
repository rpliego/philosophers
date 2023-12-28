/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:48:05 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/28 18:28:29 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	ft_clear_data(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av) != 0)
		return (1);
	init(&data, av, ac);
	init_threads(&data);
	ft_exit(&data);
	return (0);
}
