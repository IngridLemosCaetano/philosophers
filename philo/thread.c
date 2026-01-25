/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:15:04 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 19:10:31 by ingrid           ###   ########.fr       */
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

static void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	while (!has_someone_died(philo->data))
		usleep(200);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!has_someone_died(philo->data))
	{
		take_forks(philo);
		if (has_someone_died(philo->data))
		{
			drop_forks(philo);
			return ;
		}
		philo_eat(philo);
		drop_forks(philo);
		if (has_someone_died(philo->data))
			return ;
		philo_sleep(philo);
		if (has_someone_died(philo->data))
			return ;
		print_action(philo, "is thinking");
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->input.n_philos == 1)
	{
		one_philo_routine(philo);
		return (NULL);
	}
	philo_loop(philo);
	return (NULL);
}
