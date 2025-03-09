/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:38:05 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 16:38:05 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	accurate_sleep(long long time_in_ms)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	while (1)
	{
		current_time = get_time();
		if (time_diff(start_time, current_time) >= time_in_ms)
			break ;
		usleep(100);
	}
}

void	print_status(t_table *table, int id, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&table->print_mutex);
	if (table->simulation_running)
	{
		timestamp = time_diff(table->start_time, get_time());
		printf("%lld %d %s\n", timestamp, id, status);
	}
	pthread_mutex_unlock(&table->print_mutex);
}
