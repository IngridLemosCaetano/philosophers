/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:15:04 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/21 16:13:53 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_data *d)
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
	return (0);
}

void	join_philo_threads(t_data *d)
{
	int	i;
	
	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_join(d->philos[i].thread, NULL);
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
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_timestamp(philo->data);
	pthread_mutex_unlock(&philo->data->death_mutex);
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
	while (1)
	{
		take_forks(philo);
		if (philo->data->someone_died)
		{
			drop_forks(philo);
			return NULL;
		}
		philo_eat(philo);
		drop_forks(philo);
		if (philo->data->someone_died)
		return NULL;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->input.time_to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
