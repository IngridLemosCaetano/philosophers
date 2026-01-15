/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:11 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/15 19:12:53 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_input
{
	long	n_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
}	t_input;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_input			input;
	t_philo			*philos;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

//parse.c
void	parse_init(int ac, char *av[], t_data *d);

//utils.c
int		is_space(char c);
void	print_error(char *message);
void	print_error_input(void);
void	print_action(t_philo *philo, char *action);
long	ft_atol(char *s);

//mutexes
void	init_mutexes(t_data *d);

//philo.c
void	init_philos(t_data *d);
void	create_thread(t_data *d);

#endif