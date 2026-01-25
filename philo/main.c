/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:20:25 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/25 16:28:19 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_all(t_data *d)
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

int	main(int ac, char *av[])
{
	t_data		d;
	pthread_t	monitor;

	parse_init(ac, av, &d);
	init_mutexes(&d);
	init_philos(&d);
	d.start_time = get_timestamp(&d);
	if (pthread_create(&monitor, NULL, ft_monitor, &d) != 0)
		return (1);
	if (create_philo_threads(&d) != 0)
		return (1);
	join_philo_threads(&d);
	pthread_join(monitor, NULL);
	clear_all(&d);
	return (0);
}

long	get_timestamp(t_data *d)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - d->start_time;
	return (time);
}
