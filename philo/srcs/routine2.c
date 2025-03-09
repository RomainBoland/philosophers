/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:19:43 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 18:19:43 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_status(philo->table, philo->id, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->table->check_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->check_mutex);
	print_status(philo->table, philo->id, "is eating");
	accurate_sleep(philo->table->time_to_eat);
	release_forks(philo);
}
