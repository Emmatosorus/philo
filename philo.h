/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:38:14 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 16:46:22 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_main	t_main;

typedef struct s_fork
{
	bool			is_taken;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_philo
{
	long			id;
	long			time_since_eat;
	long			nb_eat;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_main			*main_ptr;
	pthread_mutex_t	lock;
}			t_philo;

typedef struct s_main
{
	t_philo			*philo_info;
	pthread_t		*philos_threads;
	t_fork			*forks;
	long			nb_philo;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			nb_meals;
	bool			end_sim;
	bool			start_watching;
	long			threads_ready;
	long			timestamp;
	pthread_mutex_t	lock;
	pthread_mutex_t	write_lock;
}				t_main;

// #### FUNCTIONS ####

// FILE actions.c
void	print_msg(char *msg, t_philo *philo, bool end);
void	eat(t_philo *philo);

// FILE utils.c
int		ft_atoi(const char *str);
void	*ft_memset(void *s, int c, size_t n);
long	get_time(void);
void	ft_sleep(long us);
void	free_main(t_main *main, char *msg);

// FILE parse.c
int		convert_input(char **av, t_main *main);

// FILE routine.c
void	*routine(void *philo);

// FILE create_philosophers.c
int		allocate_philosophers(t_main *main);
int		create_philosophers(t_main *main);

// FILE mutex_helpers.c
long	get_long(const long *value, pthread_mutex_t *lock);
bool	get_bool(const bool *value, pthread_mutex_t *lock);
void	set_bool(bool *var, bool value, pthread_mutex_t *lock);
void	set_long(long *var, long value, pthread_mutex_t *lock);

#endif //PHILO_H
