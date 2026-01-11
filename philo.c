/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:00 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/11 20:12:38 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	init_philos(t_data *d)
// {
// 	int	i;

// 	i = 0;
// 	d->philos->last_meal = 0;
// 	d->philos->meals_eaten = 0;
// 	d->philos = malloc(sizeof(t_philos) * d->input.n_philos);
// 	if (!d->philos)
// 		printf_error("malloc philos")
// 	while (i < d->philos->n_philos)
// 	{
// 		d->philos[i]->id = i + 1;
// 		d->philos[i].right_fork = &d->forks[i];
// 		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
// 		if (pthread_mutex_init(&d->philos[i], NULL) != 0)
// 			printf_error("mutex");
// 		d->philos[i]->meals_eaten = 0;
// 		i++;
// 	}
// }

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

void	*philo_routine(void *arg)
{
	
}
