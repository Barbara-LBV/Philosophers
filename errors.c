/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:05:11 by blefebvr          #+#    #+#             */
/*   Updated: 2023/01/31 16:46:52 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char c)
{
	if (c >= 48 && c <= 58)
		return (1);
	return (0);
}

int	check_data(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (is_number(av[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_errors(t_data *data, int ac, char **av)
{
	if (check_data(ac, av))
		return (print_data_errors(data, 2));
	else if (data->nb_philo == 0)
		return (print_data_errors(data, 3));
	else if (data-> time_to_die == 0)
		return (print_data_errors(data, 4));
	else if (data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (print_data_errors(data, 5));
	else if (ac == 6 && data->nb_of_eat == 0)
		return (print_data_errors(data, 6));
	return (0);
}

int	print_data_errors(t_data *data, int errnb)
{
	if (errnb == 1)
		printf("Wrong numbers of arguments\n");
	else if (errnb == 2)
		printf("Invalid arguments\n");
	else if (errnb == 3)
		printf("Invalid number of Philos\n");
	else if (errnb == 4)
		printf("Invalid time to die\n");
	else if (errnb == 5)
		printf("Invalid time to eat or sleep\n");
	else if (errnb == 6)
		printf("Invalid number of meals\n");
	free(data);
	return (1);
}

void	print_init_errors(t_data *data, int errnb)
{
	if (errnb == 1)
		printf("Data allocation memory failed\n");
	else if (errnb == 2)
		printf("Init mutex error\n");
	else if (errnb == 3)
		printf("Philo allocation memory failed\n");
	free_data(data);
}
