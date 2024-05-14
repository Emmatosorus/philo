/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:23:09 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/14 09:18:01 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	register_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_ptr->lock);
	philo->main_ptr->threads_ready++;
	pthread_mutex_unlock(&philo->main_ptr->lock);
	while (1)
		if (get_bool(&philo->main_ptr->start_watching, &philo->main_ptr->lock))
			break ;
	set_long(&philo->time_since_eat, philo->main_ptr->timestamp, &philo->lock);
}

void	unsync_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_sleep(philo->main_ptr->time_to_eat * 0.1);
}

void	*routine(void *philo_info)
{
	t_philo			*philo;
	t_main			*main;

	philo = (t_philo *)philo_info;
	main = philo->main_ptr;
	register_start(philo);
	unsync_philo(philo);
	while (!get_bool(&main->end_sim, &main->lock))
	{
		eat(philo);
		print_msg("is sleeping", philo, false);
		ft_sleep(main->time_to_sleep);
		print_msg("is thinking", philo, false);
	}
	return (NULL);
}
