/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blefebvr <blefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:03:48 by blefebvr          #+#    #+#             */
/*   Updated: 2023/02/12 18:46:00 by blefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO

# define GREY "\033[0;90m"
# define BLUE "\033[0;34m"
# define RED "\033[1;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define WHITE "\033[00m"

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				nb_of_eat;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	long long int	last_eat;
	pthread_t		th;
	t_data			*data;
};

struct s_data
{
	int				nb_philo;
	int				nb_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				nb_of_eat;
	int				dead;
	long long int	start_time;
	long long int	end_time;
	long long int	time_spent;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	finish;
	pthread_mutex_t	*forks;
};

/* Initialization */
int				ft_atoi(const char *str);
int				check_errors(t_data *data, int ac, char **av);
int				print_data_errors(t_data *data, int errnb);
int				check_data(int ac, char **av);
int				is_number(char c);
int				init_philo(t_data *data);
int				init_mutex(t_data *data);
int				initialization(t_data *data, int ac, char **av);
int				init_data(t_data *data, char **av, int ac);
void			print_init_errors(t_data *data, int errnb);

/* Threads */
void			routine_sleep(t_philo *philo);
void			is_eating(t_philo *philo);
void			even_is_eating(t_philo *philo);
void			odd_is_eating(t_philo *philo);
void			is_thinking(t_philo *philo);
void			is_sleeping(t_philo *philo);
void			philo_action(t_philo *philo);
void			*routine(void *res);
void			activate_philo(t_data *data);
void			one_philo(t_data *data, long long int time);
void			count_meal(t_philo *philo);

/* Monitoring */
void			finish_diner(t_data *data, int i);
int				philo_check_finish(t_data *data, int forks, int i);
void			check_dead(t_data *data);
int				unlock_mutexes_odd(t_data *data, int forks, int i);
int				unlock_mutexes_even(t_data *data, int forks, int i);

/* Timing */
void			print_action(t_philo *philo, char *s);
long long int	calculate_time(void);
long long int	get_time(t_data *data);

/* Free Structs & Mutexes */
void			destroy_mutexes(t_data *data);
void			free_data(t_data *data);

#endif