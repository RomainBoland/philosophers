/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:08:58 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 17:08:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->check_mutex);
	if (table->philos)
		free(table->philos);
}
