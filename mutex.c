/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/11 18:56:57 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->input.n_philos);
	if (!d->forks)
		printf_error("malloc forks fails");
	while (i < d->input.n_philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			printf_error("init mutex");
		i++;
	}
}

//rever function
void	destroy_mutexes(t_data	*d)
{
	int	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_mutex_destroy(&d->forks[i])
		i++;
	}
	pthread_mutex_destroy(&d->print_mutex);
}
