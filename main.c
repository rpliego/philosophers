/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:48:05 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/29 16:25:52 by rpliego          ###   ########.fr       */
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
	exit(0);
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
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->mutx_dead);
	pthread_mutex_destroy(&data->mutx_finish);
	ft_clear_data(data);
}

void	case_one(t_data *data)
{
	data->start_time = get_time();
	print_status(FORK, &data->philos[0]);
	print_status(THINK, &data->philos[0]);
	ft_usleep(data->death_time);
	print_status(DIED, &data->philos[0]);
	ft_exit(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av) != 0)
		return (1);
	init(&data, av, ac);
	if (data.philo_nb == 1)
		case_one(&data);
	init_threads(&data);
	ft_exit(&data);
	return (0);
}
