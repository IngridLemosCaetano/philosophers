/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/19 17:06:44 by ilemos-c         ###   ########.fr       */
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
}
