/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:12 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 16:16:03 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_philosophers(t_main *main)
{
	main->philo_info = (t_philo *)malloc((main->nb_philo) * sizeof(t_philo));
	if (!main->philo_info)
		return (1);
	ft_memset(main->philo_info, 0, main->nb_philo);
	main->forks = (t_fork *)malloc((main->nb_philo) * sizeof(t_fork));
	if (!main->forks)
	{
		free(main->philo_info);
		return (1);
	}
	ft_memset(main->forks, 0, main->nb_philo);
	main->philos_threads = (pthread_t *)malloc((main->nb_philo) * \
		sizeof(pthread_t));
	if (!main->philos_threads)
	{
		free(main->philo_info);
		free(main->forks);
		return (1);
	}
	return (0);
}

void	hand_out_forks(t_philo *philo, t_fork *forks, int i, long nb_philo)
{
	philo->l_fork = &forks[(i + 1) % nb_philo];
	philo->r_fork = &forks[i];
	if (philo->id % 2 == 0)
	{
		philo->l_fork = &forks[i];
		philo->r_fork = &forks[(i + 1) % nb_philo];
	}
}

int	create_philosophers(t_main *main)
{
	int				i;

	i = -1;
	pthread_mutex_init(&main->lock, NULL);
	pthread_mutex_init(&main->write_lock, NULL);
	while (++i < main->nb_philo)
	{
		main->philo_info[i].id = i + 1;
		main->philo_info[i].nb_eat = main->nb_meals;
		main->philo_info[i].main_ptr = main;
		main->philo_info[i].time_since_eat = LONG_MAX;
		hand_out_forks(&main->philo_info[i], main->forks, i, main->nb_philo);
		pthread_mutex_init(&main->philo_info[i].lock, NULL);
		pthread_mutex_init(&main->forks[i].lock, NULL);
		if (pthread_create(&main->philos_threads[i], NULL, &routine, \
			&main->philo_info[i]) != 0)
			return (1);
	}
	return (0);
}
