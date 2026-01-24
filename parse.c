/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:32:05 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 12:34:30 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		has_digit = 1;
		i++;
	}
	while (is_space(s[i]))
		i++;
	if (has_digit && s[i] == '\0')
		return (1);
	return (0);
}

static void	validate_args(int ac, char *av[])
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		print_error_input();
	while (i < ac)
	{
		if (!is_num(av[i]))
			print_error_input();
		i++;
	}
}

static long	parse_value(char *s)
{
	long	value;

	value = ft_atol(s);
	if (value <= 0 || value > INT_MAX)
		print_error_input();
	return (value);
}

void	parse_init(int ac, char *av[], t_data *d)
{
	memset(d, 0, sizeof(t_data));
	validate_args(ac, av);
	d->input.n_philos = parse_value(av[1]);
	d->input.time_to_die = parse_value(av[2]);
	d->input.time_to_eat = parse_value(av[3]);
	d->input.time_to_sleep = parse_value(av[4]);
	d->someone_died = 0;
	if (ac == 6)
	{
		d->input.must_eat = parse_value(av[5]);
		d->all_ate = 0;
	}
	else
		d->input.must_eat = -1;
}
