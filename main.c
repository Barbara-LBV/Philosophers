/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:03:56 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/13 17:06:20 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		print_init_errors(data, 1);
		return (0);
	}
	if (initialization(data, ac, av))
		return (0);
	one_philo(data, data->time_to_die);
	data->start_time = calculate_time();
	activate_philo(data);
	free_data(data);
	return (0);
}
