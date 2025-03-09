/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:10:31 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 17:10:31 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	parse_args(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->num_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (false);
	if (argc == 6)
	{
		table->meals_required = ft_atoi(argv[5]);
		if (table->meals_required <= 0)
			return (false);
	}
	else
		table->meals_required = -1;
	return (true);
}

bool	init_table(t_table *table, int argc, char **argv)
{
	table->philos = NULL;
	table->forks = NULL;
	if (!parse_args(table, argc, argv))
	{
		printf("Failed to parse arguments\n");
		return (false);
	}
	table->simulation_running = true;
	if (!init_mutexes(table))
	{
		return (false);
	}
	if (!init_philos(table))
	{
		cleanup(table);
		return (false);
	}
	return (true);
}

bool	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (false);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->check_mutex, NULL) != 0)
		return (false);
	return (true);
}

bool	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (false);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->num_philos;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		i++;
	}
	return (true);
}
