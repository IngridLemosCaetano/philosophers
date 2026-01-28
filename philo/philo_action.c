/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:00:08 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 19:14:51 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
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
/*
void	*take_forks(t_philo *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (p->left_fork < p->right_fork)
	{
		first_fork = p->left_fork;
		second_fork = p->right_fork;
	}
	else
	{
		first_fork = p->right_fork;
		second_fork = p->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_action(p, "has taken a fork");
	if (p->data->input.n_philos == 1)
	{
		ft_usleep(p->data->input.time_to_die, p->data);
		pthread_mutex_unlock(first_fork);
		return (NULL);
	}
	pthread_mutex_lock(second_fork);
	print_action(p, "has taken a fork");
	return (NULL);
}*/

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_timestamp(philo->data);
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is eating");
	philo->meals_eaten++;
	if (philo->data->input.must_eat > 0
		&& philo->meals_eaten == philo->data->input.must_eat)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->all_ate++;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	ft_usleep(philo->data->input.time_to_eat, philo->data);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo	*philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->input.time_to_sleep, philo->data);
}
