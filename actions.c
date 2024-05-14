/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:57:38 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/14 09:25:35 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	print_msg(char *msg, t_philo *philo, bool end)
{
	pthread_mutex_lock(&philo->main_ptr->write_lock);
	if (!get_bool(&philo->main_ptr->end_sim, &philo->main_ptr->lock) || end)
	{
		printf("%ld\t%ld\t%s\n", (get_time() - philo->main_ptr->timestamp) / \
			1000, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->main_ptr->write_lock);
}

void	take_fork(t_fork *l_fork, t_fork *r_fork, t_philo *philo)
{
	int	fork_count;

	fork_count = 0;
	while (fork_count != 2 && !get_bool(&philo->main_ptr->end_sim, \
		&philo->main_ptr->lock))
	{
		pthread_mutex_lock(&l_fork->lock);
		if (!l_fork->is_taken)
		{
			l_fork->is_taken = true;
			print_msg("has taken a fork", philo, false);
			fork_count++;
		}
		pthread_mutex_unlock(&l_fork->lock);
		pthread_mutex_lock(&r_fork->lock);
		if (!r_fork->is_taken)
		{
			r_fork->is_taken = true;
			print_msg("has taken a fork", philo, false);
			fork_count++;
		}
		pthread_mutex_unlock(&r_fork->lock);
		ft_sleep(200);
	}
}

inline void	eat(t_philo *philo)
{
	t_main	*main;

	main = philo->main_ptr;
	take_fork(philo->l_fork, philo->r_fork, philo);
	print_msg("is eating", philo, false);
	set_long(&philo->time_since_eat, get_time(), &philo->lock);
	ft_sleep(main->time_to_eat);
	set_bool(&philo->l_fork->is_taken, false, &philo->l_fork->lock);
	set_bool(&philo->r_fork->is_taken, false, &philo->r_fork->lock);
	pthread_mutex_lock(&philo->lock);
	philo->nb_eat--;
	pthread_mutex_unlock(&philo->lock);
}
