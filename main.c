/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:20:25 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/18 21:38:23 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data	d;

	parse_init(ac, av, &d);
	init_mutexes(&d);
	init_philos(&d);
	d.start_time = get_timestamp(&d);
	if (create_thread(&d) != 0)
	{
		clear_all(&d);
		return (1);
	}
	clear_all(&d);
	return (0);
}
