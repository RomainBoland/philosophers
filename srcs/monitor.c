/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:08:45 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 17:08:45 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_table *table, int *i)
{
	long long	current_time;
	long long	time_since_last_meal;
	
	// Ensure table and philosopher array exist
	if (!table || !table->philos)
		return (true);
		
	pthread_mutex_lock(&table->check_mutex);
	current_time = get_time();
	
	// Check if index is valid
	if (*i >= 0 && *i < table->num_philos)
	{
		time_since_last_meal = time_diff(table->philos[*i].last_meal_time, 
									current_time);
		
		if (time_since_last_meal > table->time_to_die)
		{
			table->simulation_running = false;
			pthread_mutex_unlock(&table->check_mutex);
			
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld %d died\n", 
				time_diff(table->start_time, current_time), 
				table->philos[*i].id);
			pthread_mutex_unlock(&table->print_mutex);
			
			return (true);
		}
	}
	pthread_mutex_unlock(&table->check_mutex);
	
	*i = (*i + 1) % table->num_philos;
	return (false);
}

bool	check_meals(t_table *table)
{
	int	i;
	int	philos_finished;

	if (table->meals_required == -1)
		return (false);
	
	i = 0;
	philos_finished = 0;
	pthread_mutex_lock(&table->check_mutex);
	while (i < table->num_philos)
	{
		if (table->philos[i].meals_eaten >= table->meals_required)
			philos_finished++;
		i++;
	}
	if (philos_finished == table->num_philos)
	{
		table->simulation_running = false;
		pthread_mutex_unlock(&table->check_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->check_mutex);
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	usleep(1000);
	while (table->simulation_running)
	{
		if (check_death(table, &i) || check_meals(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
