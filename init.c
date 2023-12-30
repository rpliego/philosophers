/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:27:32 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/30 20:26:59 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eating = 0;
		data->philos[i].finished = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->philo_nb - 1];
	i = 1;
	while (i < data->philo_nb)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
}

void	init_malloc(t_data *data)
{
	data->tid = malloc(data->philo_nb * sizeof(pthread_t));
	if (!data->tid)
		ft_clear_data(data);
	data->forks = malloc(data->philo_nb * sizeof(pthread_mutex_t));
	if (!data->forks)
		ft_clear_data(data);
	data->philos = malloc(data->philo_nb * sizeof(t_philo));
	if (!data->philos)
		ft_clear_data(data);
}

void	init_data(t_data *data, char **av, int ac)
{
	data->philo_nb = (int)ft_atoi(av[1]);
	data->death_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = (int)ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	data->dead = 0;
	data->finish_all = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
}

void	init(t_data *data, char **av, int ac)
{
	init_data(data, av, ac);
	init_malloc(data);
	init_mutex(data);
	init_philo(data);
}
