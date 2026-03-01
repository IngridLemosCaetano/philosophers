/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:11 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/04 14:05:12 by ilemos-c         ###   ########.fr       */
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
	pthread_mutex_t	meal_mutex;
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

int		valid_init(t_data *d, int ac, char *av[]);

void	*ft_monitor(void *arg);
void	ft_usleep(long ms, t_data *d);
int		has_someone_died(t_data *d);

int		parse_init(int ac, char *av[], t_data *d);

void	*philo_routine(void *arg);

int		create_threads(t_data *d);
void	join_threads(t_data *d);
void	clear_all(t_data *d);

int		is_space(char c);
long	ft_atol(char *s);
void	print_action(t_philo *philo, char *action);
long	get_timestamp(t_data *d);
long	get_timestamp_ms(void);

#endif
