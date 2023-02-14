/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:38:57 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/13 15:32:52 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_check_finish(t_data *data, int forks, int i)
{
	int	lock;

	pthread_mutex_lock(&data->finish);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->finish);
		if (data->nb_philo % 2 == 1)
			lock = unlock_mutexes_odd(data, forks, i);
		else
			lock = unlock_mutexes_even(data, forks, i);
		return (lock);
	}
	pthread_mutex_unlock(&data->finish);
	return (0);
}

void	check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (data->dead == 0)
	{
		pthread_mutex_lock(&data->meal);
		if (data->philo[i].nb_of_eat == 0)
		{
			pthread_mutex_unlock(&data->meal);
			break ;
		}
		if ((calculate_time() - data->philo[i].last_eat) >= data->time_to_die
			&& data->philo[i].nb_of_eat != 0)
		{
			finish_diner(data, i);
			break ;
		}
		pthread_mutex_unlock(&data->meal);
		if (i == (data->nb_philo - 1))
			i = -1;
		i++;
		usleep(50);
	}
}

void	finish_diner(t_data *data, int i)
{
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->finish);
	data->dead = 1;
	pthread_mutex_unlock(&data->finish);
	print_action(&data->philo[i], RED "is dead\n" WHITE);
}
