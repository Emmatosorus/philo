/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:57:38 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 16:20:39 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *msg, t_philo *philo, bool end)
{
	if (!get_bool(&philo->main_ptr->end_sim, &philo->main_ptr->lock) || end)
	{
		pthread_mutex_lock(&philo->main_ptr->write_lock);
		printf("%ld\t%ld\t%s\n", get_time() - \
			get_long(&philo->main_ptr->timestamp, &philo->main_ptr->lock), \
			get_long(&philo->id, &philo->lock), msg);
		pthread_mutex_unlock(&philo->main_ptr->write_lock);
	}
}

int	watch_fork(t_fork *fork, t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&fork->lock);
	if (!fork->is_taken)
	{
		fork->is_taken = true;
		print_msg("has taken a fork", philo, false);
		ret = 1;
	}
	pthread_mutex_unlock(&fork->lock);
	return (ret);
}

void	eat(t_philo *philo)
{
	while (watch_fork(philo->l_fork, philo) != 1)
		if (get_bool(&philo->main_ptr->end_sim, &philo->main_ptr->lock))
			return ;
	while (watch_fork(philo->r_fork, philo) != 1)
		if (get_bool(&philo->main_ptr->end_sim, &philo->main_ptr->lock))
			return ;
	print_msg("is eating", philo, false);
	set_long(&philo->time_since_eat, get_time(), &philo->lock);
	ft_sleep(get_long(&philo->main_ptr->time_to_eat, &philo->main_ptr->lock));
	set_bool(&philo->l_fork->is_taken, false, &philo->l_fork->lock);
	set_bool(&philo->r_fork->is_taken, false, &philo->r_fork->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->nb_eat > 0)
		philo->nb_eat--;
	pthread_mutex_unlock(&philo->lock);
}
