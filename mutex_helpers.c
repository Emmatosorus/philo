/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:22:55 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/07 16:25:19 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_long_philo(t_philo *philo, long *nb)
{
	pthread_mutex_lock(&philo->lock);
	*nb = philo->time_since_eat;
	pthread_mutex_unlock(&philo->lock);
}

void	get_long_main(t_main *main, long *nb)
{
	pthread_mutex_lock(&main->lock);
	*nb = main->time_to_die;
	pthread_mutex_unlock(&main->lock);
}

int	is_end(t_main *main)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&main->lock);
	if (!main->end_sim)
		ret = 1;
	pthread_mutex_unlock(&main->lock);
	return (ret);
}

int	finished_eating(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->lock);
	if (philo->nb_eat > 0)
		ret = 1;
	pthread_mutex_unlock(&philo->lock);
	return (ret);
}

void	unsync_philo(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->main_ptr->lock);
		usleep(philo->main_ptr->time_to_eat / 10);
		pthread_mutex_unlock(&philo->main_ptr->lock);
	}
}
