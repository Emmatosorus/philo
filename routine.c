/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:23:09 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 16:19:38 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	set_long(&philo->time_since_eat, get_time(), &philo->lock);
}

void	unsync_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->main_ptr->lock);
		usleep(philo->main_ptr->time_to_eat * 0.1);
		pthread_mutex_unlock(&philo->main_ptr->lock);
	}
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
		print_msg("is sleeping", philo, false);
		ft_sleep(get_long(&philo->main_ptr->time_to_sleep, \
			&philo->main_ptr->lock));
		print_msg("is thinking", philo, false);
	}
	return (NULL);
}
