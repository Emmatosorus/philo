/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:38:14 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/06 17:32:19 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_GIT_PHILO_H
#define PHILO_GIT_PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct  s_main t_main;

typedef struct s_fork
{
	bool			is_taken;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	long			time_since_eat;
	long			nb_eat;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_main			*ptr;
	pthread_mutex_t	lock;
}			t_philo;

typedef struct s_main
{
	t_philo			*philos;
	t_fork			*forks;
	long			nb_philo;
	long			time_to_eat;
	long			time_to_sleep;
	long 			time_to_die;
	long			nb_meals;
	bool			end_sim;
	bool			start_watching;
	long 			threads_ready;
	long 			timestamp;
	pthread_mutex_t	lock;
}				t_main;

// #### FUNCTIONS ####

// FILE utils.c
int		ft_atoi(const char *str);

// FILE parse.c
int		convert_input(char **av, t_main *main);

// FILE routine.c
void	*routine(void *philo);

#endif //PHILO_GIT_PHILO_H
