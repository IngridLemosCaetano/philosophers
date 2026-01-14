/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:22:00 by ingrid            #+#    #+#             */
/*   Updated: 2026/01/14 17:07:36 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	init_philos(t_data *d)
// {
// 	int	i;

// 	i = 0;
// 	d->philos->last_meal = 0;
// 	d->philos->meals_eaten = 0;
// 	d->philos = malloc(sizeof(t_philos) * d->input.n_philos);
// 	if (!d->philos)
// 		printf_error("malloc philos")
// 	while (i < d->philos->n_philos)
// 	{
// 		d->philos[i]->id = i + 1;
// 		d->philos[i].right_fork = &d->forks[i];
// 		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
// 		if (pthread_mutex_init(&d->philos[i], NULL) != 0)
// 			printf_error("mutex");
// 		d->philos[i]->meals_eaten = 0;
// 		i++;
// 	}
// }

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->input.n_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].right_fork = &d->forks[i];
		d->philos[i].left_fork = &d->forks[(i + 1) % d->input.n_philos];
		d->philos[i].meals_eaten = 0;
		d->philos[i].data = d;
		i++;
	}
}

void	*philo_routine(void *arg)
{	
	t_philo			*philo;
	pthread_mutex_t	p;

	philo = (t_philo *)arg;
	// philo->last_meal = gettimeofday();
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		if (philo->id % 2 == 0)
		{
			philo->right_fork = 1;
			// printf("%d %d has taken a fork\n",philo->data->input, philo->id);
			philo->left_fork = 1;			
		}
		else
		{
			philo->left_fork = 1;
			philo->right_fork = 1;
		}
		pthread_mutex_lock(&p);
		pthread_mutex_lock(philo->left_fork);
		ft_usleep(philo->data->input.time_to_eat);
	}
}

void	ft_usleep(long time_to_eat)
{
	usleep(time_to_eat);
}