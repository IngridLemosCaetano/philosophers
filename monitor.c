/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 17:21:44 by ingrid           ###   ########.fr       */
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
		if (d->input.must_eat > 0)
		{
			pthread_mutex_lock(&d->death_mutex);
			if (d->all_ate == d->input.n_philos)
			{
				d->someone_died = 1;
				pthread_mutex_unlock(&d->death_mutex);
				printf("All philosophers have eaten enough\n");
				return (NULL);
			}
			pthread_mutex_unlock(&d->death_mutex);
		}
		i = 0;
		while (i < d->input.n_philos)
		{
			pthread_mutex_lock(&d->death_mutex);
			if ((get_timestamp(d) - d->philos[i].last_meal)
				> d->input.time_to_die)
			{
				d->someone_died = 1;
				pthread_mutex_unlock(&d->death_mutex);
				pthread_mutex_lock(&d->print_mutex);
				printf("%ld %d died\n", get_timestamp(d), d->philos[i].id);
				pthread_mutex_unlock(&d->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&d->death_mutex);
			i++;
		}
		usleep(200);
	}
}

int	has_someone_died(t_data *d)
{
	int	status;

	pthread_mutex_lock(&d->death_mutex);
	status = d->someone_died;
	pthread_mutex_unlock(&d->death_mutex);
	return (status);
}

long	get_timestamp(t_data *d)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - d->start_time;
	return (time);
}

void	ft_usleep(long ms, t_data *d)
{
	long	start;

	start = get_timestamp(d);
	while ((get_timestamp(d) - start) < ms)
	{
		pthread_mutex_lock(&d->death_mutex);
		if (d->someone_died)
		{
			pthread_mutex_unlock(&d->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&d->death_mutex);
		usleep(500);
	}
}
