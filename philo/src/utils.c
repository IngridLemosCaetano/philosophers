/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:07 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/04 14:03:42 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
}

long	get_timestamp(t_data *d)
{
	long	time;

	time = get_timestamp_ms() - d->start_time;
	return (time);
}

long	get_timestamp_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
