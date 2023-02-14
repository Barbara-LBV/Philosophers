/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:13:48 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/12 13:48:00 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	if (*str == '\0' || str == NULL)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
			str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i++] - '0';
	}
	nb *= neg;
	return (nb);
}

void	print_action(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lld : Philo %d %s\n", get_time(philo->data), philo->id, s);
	pthread_mutex_unlock(&philo->data->print);
}

void	count_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal);
	philo->last_eat = calculate_time();
	philo->nb_of_eat--;
	pthread_mutex_unlock(&philo->data->meal);
}

long long int	calculate_time(void)
{
	struct timeval	tv;
	long long int	time;

	gettimeofday(&tv, NULL);
	time = (((tv.tv_sec % 10000) * 1000) + (tv.tv_usec / 1000));
	return (time);
}

long long int	get_time(t_data *data)
{
	return (calculate_time() - data->start_time);
}
