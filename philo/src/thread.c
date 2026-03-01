/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:15:04 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/03 17:09:39 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *d)
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

void	join_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
}

static void	destroy_forks(t_data *d)
{
	int	i;

	i = 0;
	if (!d->forks)
		return ;
	while (i < d->input.n_philos)
	{
		pthread_mutex_destroy(&d->forks[i]);
		i++;
	}
	free(d->forks);
	d->forks = NULL;
}

static void	destroy_philos(t_data *d)
{
	int	i;

	if (!d->philos)
		return ;
	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_mutex_destroy(&d->philos[i].meal_mutex);
		i++;
	}
	free(d->philos);
	d->philos = NULL;
}

void	clear_all(t_data *d)
{
	if (!d)
		return ;
	destroy_forks(d);
	destroy_philos(d);
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->death_mutex);
}
