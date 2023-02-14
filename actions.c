/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:12:37 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/12 16:2:01 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (philo_check_finish(philo->data, 1, philo->id - 1) != 0)
		return ;
	print_action(philo, "has taken left fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (philo_check_finish(philo->data, 2, philo->id - 1) != 0)
		return ;
	print_action(philo, "has taken right fork\n");
	print_action(philo, "is eating\n");
	count_meal(philo);
	usleep(philo->time_to_eat * 1000);
	if (philo_check_finish(philo->data, 2, philo->id - 1) != 0)
		return ;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	odd_is_eating(t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (philo_check_finish(philo->data, 1, philo->id - 1) != 0)
		return ;
	print_action(philo, "has taken right fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (philo_check_finish(philo->data, 2, philo->id - 1) != 0)
		return ;
	print_action(philo, "has taken left fork\n");
	print_action(philo, "is eating\n");
	count_meal(philo);
	usleep(philo->time_to_eat * 1000);
	if (philo_check_finish(philo->data, 2, philo->id - 1) != 0)
		return ;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	is_sleeping(t_philo *philo)
{	
	print_action(philo, "is sleeping\n");
	usleep(philo->time_to_sleep * 1000);
	if (philo_check_finish(philo->data, 0, philo->id - 1) != 0)
		return ;
}

void	is_thinking(t_philo *philo)
{
	if (philo_check_finish(philo->data, 0, philo->id - 1) != 0)
		return ;
	print_action(philo, "is thinking\n");
}

void	one_philo(t_data *data, long long int time)
{
	if (data->nb_philo == 1)
	{
		printf("%d Philo 1 has taken left fork\n", 0);
		usleep(time * 1000);
		printf(RED "%lld Philo 1 is dead\n" WHITE, time);
		free_data(data);
		exit(1);
	}
	return ;
}
