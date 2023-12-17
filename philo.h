/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:48:43 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/07 21:11:24 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		*tid;
	int				philo_nb;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_nb;
	int				finish;
	pthread_mutex_t	*forks;
}				t_data;

int		check_args(int ac, char **av);
int		ft_atoi(char *str);
void	init(t_data *data, char **av, int ac);
void	ft_exit(t_data *data);
void	init_threads(t_data *data);

#endif