/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:20:25 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/15 18:18:58 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data	d;

	parse_init(ac, av, &d);
	init_mutexes(&d);
	init_philos(&d);
	d.start_time = 0;
	create_thread(&d);
	return (0);
}
