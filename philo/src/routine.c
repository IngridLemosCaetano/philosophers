/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:00:08 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/04 09:37:22 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	int	reached;

	reached = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_timestamp(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	if (philo->data->input.must_eat > 0
		&& philo->meals_eaten == philo->data->input.must_eat)
		reached = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (reached)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->all_ate++;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	ft_usleep(philo->data->input.time_to_eat, philo->data);
}

static int	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (p->left_fork < p->right_fork)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(first);
	print_action(p, "has taken a fork");
	if (p->data->input.n_philos == 1)
	{
		ft_usleep(p->data->input.time_to_die, p->data);
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	print_action(p, "has taken a fork");
	return (2);
}

static void	philo_sleep(t_philo	*philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->input.time_to_sleep, philo->data);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;
	int		locks;

	p = (t_philo *)arg;
	if (p->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (has_someone_died(p->data))
			return (NULL);
		locks = take_forks(p);
		if (locks < 2)
			return (NULL);
		philo_eat(p);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		philo_sleep(p);
		print_action(p, "is thinking");
	}
}
