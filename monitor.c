/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/20 10:51:51 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_monitor(t_data *d)
{
	int		i;
	long	time_now;
	long	time_without_eat;

	i = 0;
	while (!d->someone_died)
	{
		while (i < d->input.n_philos)
		{
			time_now = get_timestamp(d);
			time_without_eat = time_now - d->philos[i].last_meal;
			if (time_without_eat > d->input.time_to_die)
			{
				print_action(d->philos, "died");
				d->someone_died = 1;
			}
			i++;
		}
		usleep(1000);
	}
}
