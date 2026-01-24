/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:07 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/24 12:35:49 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	print_error(char *message)
{
	printf("Error: %s.\n", message);
	exit (EXIT_FAILURE);
}

void	print_error_input(void)
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

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
