/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:32:05 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/11 13:21:07 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	j = i;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '\0')
	{
		while (s[j] == '0')
			j++;
		if (!s[j] && s[j - 1] == '0')
			printf_error_input();
		return (1);
	}
	else
		return (0);
}

static void	valid_input(int ac, char *av[])
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		printf_error_input();
	while (av[i])
	{
		if (!is_num(av[i]))
			printf_error_input();
		i++;
	}
}

void	parse_init(int ac, char *av[], t_data *d)
{
	valid_input(ac, av);
	d->input.n_philos = ft_atol(av[1]);
	d->input.time_to_die = ft_atol(av[2]);
	d->input.time_to_eat = ft_atol(av[3]);
	d->input.time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		d->input.must_eat = ft_atol(av[5]);
	else
		d->input.must_eat = -1;
	if (d->input.n_philos > INT_MAX || d->input.time_to_die > INT_MAX
		|| d->input.time_to_eat > INT_MAX || d->input.time_to_sleep > INT_MAX
		|| d->input.must_eat > INT_MAX)
		printf_error_input();
}
