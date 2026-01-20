/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/20 13:52:04 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *arg)
{
	t_data	*d;	
	int		i;
	d = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < d->input.n_philos)
		{
			pthread_mutex_lock(&d->death_mutex);
			if ((get_timestamp(d) - d->philos[i].last_meal) > 
				d->input.time_to_die)
			{
				print_action(d->philos, "died");
				d->someone_died = 1;
				pthread_mutex_unlock(&d->death_mutex);
				return	NULL;
			}
			pthread_mutex_unlock(&d->death_mutex);
			i++;
		}
		usleep(1000);
	}
}
