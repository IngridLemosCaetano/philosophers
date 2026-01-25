/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 12:34:02 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->input.n_philos);
	if (!d->forks)
		print_error("malloc forks fails");
	while (i < d->input.n_philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			print_error("init mutex");
		i++;
	}
	if (pthread_mutex_init(&d->print_mutex, NULL) != 0)
		print_error("init mutex");
	if (pthread_mutex_init(&d->death_mutex, NULL) != 0)
		print_error("init mutex");
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	d->philos = malloc(sizeof(t_philo) * d->input.n_philos);
	if (!d->philos)
		print_error("malloc philos fails");
	while (i < d->input.n_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].right_fork = &d->forks[i];
		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		d->philos[i].last_meal = d->start_time;
		i++;
	}
}
