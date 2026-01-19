/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/19 15:23:25 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(t_data *d)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - d->start_time;
	return (time);
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	d->philos = malloc(sizeof(t_philo) * d->input.n_philos);
	if (!d->philos)
		print_error("malloc forks fails");
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

void	ft_usleep(long ms, t_data *d)
{
	long	start;

	start = get_timestamp(d);
	while ((get_timestamp(d) - start) < ms)
	{
		if (d->someone_died)
			break ;
		usleep(500);
	}
}

void	clear_all(t_data *d)
{
	int	i;

	if (!d)
		return ;
	if (d->forks)
	{
		i = 0;
		while (i < d->input.n_philos)
		{
			pthread_mutex_destroy(&d->forks[i]);
			i++;
		}
		free(d->forks);
		d->forks = NULL;
	}
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->death_mutex);
	if (d->philos)
	{
		free(d->philos);
		d->philos = NULL;
	}
}
