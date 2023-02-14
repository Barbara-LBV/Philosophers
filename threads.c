/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:03:40 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/09 13: by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activate_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].th, NULL, routine, &data->philo[i]))
			return ;
	}
	check_dead(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].th, NULL);
	return ;
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	usleep((philo->data->nb_philo + philo->id) * 1500);
	pthread_mutex_lock(&philo->data->meal);
	philo->last_eat = calculate_time();
	pthread_mutex_unlock(&philo->data->meal);
	while (philo->nb_of_eat != 0)
	{
		is_eating(philo);
		pthread_mutex_lock(&philo->data->finish);
		if (philo->data->dead != 0)
		{
			pthread_mutex_unlock(&philo->data->finish);
			break ;
		}
		pthread_mutex_unlock(&philo->data->finish);
		if (philo->nb_of_eat == 0)
			break ;
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	is_eating(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			odd_is_eating(philo);
		else
			even_is_eating(philo);
	}
	else
	{
		if (philo->id % 2 == 0)
			even_is_eating(philo);
		else
			odd_is_eating(philo);
	}
}
