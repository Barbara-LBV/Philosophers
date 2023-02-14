/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:17:48 by blefebvr          #+#    #+#             */
/*   Updated: 2023/01/17 11:17:48 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **av, int ac)
{
	if (ac != 5 && ac != 6)
		return (print_data_errors(data, 1));
	data->nb_philo = ft_atoi(av[1]);
	data->nb_fork = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_of_eat = ft_atoi(av[5]);
	else if (ac == 5)
		data->nb_of_eat = -1;
	data->dead = 0;
	data->start_time = calculate_time();
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_fork);
	if (!(data->forks))
		return (1);
	i = 0;
	while (i < data->nb_fork)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}	
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->finish, NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (1);
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = (i + 1) % data->nb_fork;
		data->philo[i].right_fork = i % data->nb_fork;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].nb_of_eat = data->nb_of_eat;
		data->philo[i].data = data;
		data->philo[i].last_eat = data->start_time;
	}
	return (0);
}

int	initialization(t_data *data, int ac, char **av)
{
	if (init_data(data, av, ac))
		return (1);
	if (check_errors(data, ac, av))
		return (1);
	else if (init_mutex(data))
		print_init_errors(data, 2);
	else if (init_philo(data))
		print_init_errors(data, 3);
	else
		return (0);
	return (1);
}
