/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:37:43 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 16:37:43 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* This function should be declared in philo.h */
bool	is_running(t_table *table);

void	sleep_philo(t_philo *philo)
{
	print_status(philo->table, philo->id, "is_sleeping");
	accurate_sleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_status(philo->table, philo->id, "is thinking");
}

static void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_status(philo->table, philo->id, "has taken a fork");
	while (is_running(philo->table))
		usleep(100);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philos == 1)
	{
		single_philo_routine(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_running(philo->table))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
