/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:26:41 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/13 16:08:24 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{	
	destroy_mutexes(data);
	free(data->forks);
	free(data->philo);
	free(data);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->finish);
	while (++i < data->nb_fork)
		pthread_mutex_destroy(&data->forks[i]);
}

int	unlock_mutexes_odd(t_data *data, int forks, int i)
{
	if (data->nb_philo % 2 == 1)
	{
		if (data->philo[i].id % 2 == 0)
		{
			if (forks >= 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].right_fork]);
			if (forks > 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
		}
		else
		{
			if (forks >= 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
			if (forks > 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].right_fork]);
		}
	}
	return (1);
}

int	unlock_mutexes_even(t_data *data, int forks, int i)
{
	if (data->nb_philo % 2 == 0)
	{
		if (data->philo[i].id % 2 == 0)
		{
			if (forks >= 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].right_fork]);
			if (forks > 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
		}
		else
		{
			if (forks >= 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].left_fork]);
			if (forks > 1)
				pthread_mutex_unlock(&data->forks[data->philo[i].right_fork]);
		}
	}
	return (2);
}
