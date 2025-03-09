/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:26:54 by rboland           #+#    #+#             */
/*   Updated: 2025/03/09 16:26:54 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

/* Colors definition*/

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* Struct Definition*/

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	long long	last_meal_time;
	pthread_t	thread;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	bool			simulation_running;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_mutex;
}	t_table;

/* Function Prototypes */

// init.c
bool		init_table(t_table *table, int argc, char **argv);
bool		init_philos(t_table *table);
bool		init_mutexes(t_table *table);

// utils.c
long long	get_time(void);
long long	time_diff(long long past, long long present);
void		accurate_sleep(long long time_in_ms);
void		print_status(t_table *table, int id, char *status);
char		*get_philo_color(int id);

// utils2.c
int			ft_atoi(const char *str);

// routine.c
void		*philo_routine(void *arg);
void		think(t_philo *philo);
void		sleep_philo(t_philo *philo);

// routine2.c
void		eat(t_philo *philo);

// monitor.c
bool		check_death(t_table *table, int *i);
bool		check_meals(t_table *table);
void		*monitor_routine(void *arg);

// cleanup.c
void		cleanup(t_table *table);

#endif