/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:07 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/11 13:09:35 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	printf_error(char *message)
{
	printf("Error: %s.\n", message);
	exit (EXIT_FAILURE);
}

void	printf_error_input(void)
{
	printf("Error: invalid input.\n");
	exit (EXIT_FAILURE);
}

long	ft_atol(char *s)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i] - 48);
		i++;
	}
	return (nb);
}
