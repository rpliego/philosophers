/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpliego <rpliego@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:48:43 by rpliego           #+#    #+#             */
/*   Updated: 2023/12/28 19:43:20 by rpliego          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/*--------macros------*/
// # define FORK_R -1
// # define FORK_L -2
# define FORK 1
# define EATING 2
# define SLEEP 3
# define THINK 4
# define DIED 5

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_count;
	int				eating;
	int				finished;
	long			time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	pthread_t		sp;
	int				philo_nb;
	long			death_time;
	long			eat_time;
	long			sleep_time;
	int				meals_nb;
	int				dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	t_philo			*philos;
}				t_data;

/*--------args------*/
int		check_args(int ac, char **av);
long	ft_atoi(char *str);

/*--------init------*/
void	init(t_data *data, char **av, int ac);
void	init_threads(t_data *data);

/*--------time------*/
long	get_time(void);
void	ft_usleep(long long time);

/*--------actions------*/
void	eat(t_philo *philo);
void	print_status(int status, t_philo *philo);

/*--------aux------*/
void	ft_clear_data(t_data *data);

#endif