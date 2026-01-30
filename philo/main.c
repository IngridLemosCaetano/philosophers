/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:20:25 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/30 16:21:01 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data		d;
	pthread_t	monitor;

	parse_init(ac, av, &d);
	init_mutexes(&d);
	d.start_time = get_timestamp_ms();
	init_philos(&d);
	if (pthread_create(&monitor, NULL, ft_monitor, &d) != 0)
		return (1);
	if (create_philo_threads(&d) != 0)
		return (1);
	join_philo_threads(&d);
	pthread_join(monitor, NULL);
	clear_all(&d);
	return (0);
}
