/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:00 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/11 17:07:44 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data d)
{
	int	i;

	i = 1;
	d->philos->last_meal = 0;
	d->philos->meals_eaten = 0;
	while (i < d->philos->n_philos)
	{
		d->philos->id = i;
		i++;
	}
}
