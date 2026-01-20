/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:15:04 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/20 09:15:34 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_data *d)
{
	long	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		if (pthread_create(&d->philos[i].thread, NULL, philo_routine,
				&d->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
	return (0);
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
	philo->last_meal = get_timestamp(philo->data);
	print_action(philo, "is eating");
	philo->meals_eaten++;
	ft_usleep(philo->data->input.time_to_eat, philo->data);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		print_action(philo, "is thinking");
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->input.time_to_sleep, philo->data);
	}
	return (NULL);
}
