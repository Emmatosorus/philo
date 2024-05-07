/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:23:09 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/07 16:21:51 by epolitze         ###   ########.fr       */
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
	{
		pthread_mutex_lock(&philo->main_ptr->lock);
		if (philo->main_ptr->start_watching)
			start = true;
		pthread_mutex_unlock(&philo->main_ptr->lock);
	}
}

void	*routine(void *philo_info)
{
	t_philo			*philo;

	philo = (t_philo *)philo_info;
	register_start(philo);
	unsync_philo(philo);
	while (is_end(philo->main_ptr) != 0)
	{
		eat(philo);
		print_msg("is sleeping", philo);
		ft_sleep(philo->main_ptr->time_to_sleep);
		print_msg("is thinking", philo);
	}
	return (NULL);
}
