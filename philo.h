/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:11 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 19:16:37 by ingrid           ###   ########.fr       */
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
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			last_meal;
	long			meals_eaten;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_input			input;
	t_philo			*philos;
	long			start_time;
	int				someone_died;
	int				all_ate;
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
long	ft_atol(char *s);
void	print_action(t_philo *philo, char *action);

//init_mutex_philo
void	init_mutexes(t_data *d);
void	init_philos(t_data *d);

//thread.c
int		create_philo_threads(t_data *d);
void	*philo_routine(void *arg);
void	join_philo_threads(t_data *d);

//monitor.c
void	*ft_monitor(void *arg);
void	ft_usleep(long ms, t_data *d);
int		has_someone_died(t_data *d);

//philo_action.c
void	take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	drop_forks(t_philo *philo);
void	philo_sleep(t_philo	*philo);

long	get_timestamp(t_data *d);

#endif
