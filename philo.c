/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:00 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/15 19:19:07 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].right_fork = &d->forks[i];
		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		i++;
	}
}

static void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{		
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->input.time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	create_thread(t_data *d)
{
	long	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		if (pthread_create(&d->philos[i].thread, NULL, philo_routine,
				&d->philos[i]) != 0)
			print_error("thread creation failed");
		i++;
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	printf("%ld %d is eating\n", philo->data->start_time, philo->id);
	usleep(philo->data->input.time_to_eat);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}