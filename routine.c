/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:23:09 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 09:21:27 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unsync_philo(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->main_ptr->lock);
		usleep(philo->main_ptr->time_to_eat / 10);
		pthread_mutex_unlock(&philo->main_ptr->lock);
	}
}

void	register_start(t_philo *philo)
{
	bool	start;

	start = false;
	pthread_mutex_lock(&philo->main_ptr->lock);
	philo->main_ptr->threads_ready++;
	pthread_mutex_unlock(&philo->main_ptr->lock);
	while (!start)
		if (get_bool(&philo->main_ptr->start_watching, &philo->main_ptr->lock))
			start = true;
}

void	*routine(void *philo_info)
{
	t_philo			*philo;

	philo = (t_philo *)philo_info;
	register_start(philo);
	unsync_philo(philo);
	while (!get_bool(&philo->main_ptr->end_sim, &philo->main_ptr->lock))
	{
		eat(philo);
		print_msg("is sleeping", philo);
		ft_sleep(philo->main_ptr->time_to_sleep);
		print_msg("is thinking", philo);
	}
	return (NULL);
}
