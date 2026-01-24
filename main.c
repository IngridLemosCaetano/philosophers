/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:20:25 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 18:34:01 by ingrid           ###   ########.fr       */
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

static void	one_philo_case(t_data *d)
{
	pthread_mutex_init(&d->print_mutex, NULL);
	pthread_mutex_init(&d->death_mutex, NULL);
	d->start_time = get_timestamp(d);
	pthread_mutex_lock(&d->print_mutex);
	printf("%ld 1 has taken a fork\n", get_timestamp(d));
	pthread_mutex_unlock(&d->print_mutex);
	ft_usleep(d->input.time_to_die, d);
	pthread_mutex_lock(&d->print_mutex);
	printf("%ld 1 died\n", get_timestamp(d));
	pthread_mutex_unlock(&d->print_mutex);
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->death_mutex);
}

int	main(int ac, char *av[])
{
	t_data		d;
	pthread_t	monitor;

	parse_init(ac, av, &d);
	if (d.input.n_philos == 1)
	{
		one_philo_case(&d);
		return (0);
	}
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
