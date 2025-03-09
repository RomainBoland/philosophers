/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:15:56 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 16:15:56 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	table->start_time = get_time();
	if (table->start_time == -1)
		return (false);
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, table) != 0)
		return (false);
	pthread_detach(monitor);
	return (true);
}

static void	wait_for_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

static bool	check_nb_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[numbers_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	return (true);
}

static bool	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (!check_nb_args(argc, argv))
		return (false);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Arguments must be positive integers\n");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_args(argc, argv))
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	if (!start_simulation(&table))
	{
		cleanup(&table);
		return (1);
	}
	wait_for_philosophers(&table);
	cleanup(&table);
	return (0);
}
