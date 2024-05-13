/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:08:12 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 09:31:38 by epolitze         ###   ########.fr       */
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
	main->philos_threads = (pthread_t *) malloc((main->nb_philo) * sizeof(pthread_t));
	if (!main->philos_threads)
	{
		free(main->philo_info);
		free(main->forks);
		return (1);
	}
	return (0);
}

int	create_philosophers(t_main *main)
{
	int				i;

	i = -1;
	while (++i < main->nb_philo)
	{
		main->philo_info[i].id = i + 1;
		main->philo_info[i].nb_eat = main->nb_meals;
		main->philo_info[i].main_ptr = main;
		main->philo_info[i].l_fork = &main->forks[i];
		if (i != main->nb_philo)
			main->philo_info[i].r_fork = &main->forks[i + 1];
		else if (main->nb_philo != 1)
			main->philo_info[i].r_fork = &main->forks[0];
		pthread_mutex_init(&main->philo_info[i].lock, NULL);
		pthread_mutex_init(&main->forks[i].lock, NULL);
		if (pthread_create(&main->philos_threads[i], NULL, &routine, &main->philo_info[i]) != 0)
			return (1);
	}
	return (0);
}