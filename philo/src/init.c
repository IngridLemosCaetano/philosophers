/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/03 16:33:19 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_error(char *message)
{
	printf("Error: %s.\n", message);
	return (1);
}

static int	init_mutexes(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->input.n_philos);
	if (!d->forks)
		return (print_error("malloc forks fails"));
	while (i < d->input.n_philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			return (print_error("Fails init fork mutex"));
		i++;
	}
	if (pthread_mutex_init(&d->print_mutex, NULL) != 0)
		return (print_error("Fails init print_mutex"));
	if (pthread_mutex_init(&d->death_mutex, NULL) != 0)
		return (print_error("Fails init death_mutex"));
	return (0);
}

static int	init_philos(t_data *d)
{
	int	i;

	i = 0;
	d->philos = malloc(sizeof(t_philo) * d->input.n_philos);
	if (!d->philos)
		return (print_error("malloc philos fails"));
	while (i < d->input.n_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].right_fork = &d->forks[i];
		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		d->philos[i].last_meal = 0;
		if (pthread_mutex_init(&d->philos[i].meal_mutex, NULL) != 0)
			return (print_error("Fails init meal_mutex"));
		i++;
	}
	return (0);
}

int	valid_init(t_data *d, int ac, char *av[])
{
	if (parse_init(ac, av, d))
	{
		printf("Error: invalid input.\n");
		return (1);
	}
	d->start_time = get_timestamp_ms();
	if (init_mutexes(d))
		return (1);
	if (init_philos(d))
		return (1);
	return (0);
}
