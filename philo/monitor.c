/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:21:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/25 14:07:53 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_data *d)
{
	if (d->input.must_eat <= 0)
		return (0);
	pthread_mutex_lock(&d->death_mutex);
	if (d->all_ate == d->input.n_philos)
	{
		d->someone_died = 1;
		pthread_mutex_unlock(&d->death_mutex);
		printf("All the philosophers have eaten enough.\n");
		return (1);
	}
	pthread_mutex_unlock(&d->death_mutex);
	return (0);
}

static int	check_death(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		pthread_mutex_lock(&d->death_mutex);
		if ((get_timestamp(d) - d->philos[i].last_meal) > d->input.time_to_die)
		{
			d->someone_died = 1;
			pthread_mutex_unlock(&d->death_mutex);
			pthread_mutex_lock(&d->print_mutex);
			printf("%ld %d died\n", get_timestamp(d), d->philos[i].id);
			pthread_mutex_unlock(&d->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&d->death_mutex);
		i++;
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*d;

	d = (t_data *)arg;
	while (1)
	{
		if (check_all_ate(d))
			return (NULL);
		if (check_death(d))
			return (NULL);
		usleep(1000);
	}
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
