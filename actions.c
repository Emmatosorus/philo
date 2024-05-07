/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:57:38 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/07 16:22:25 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->main_ptr->lock);
	if (!philo->main_ptr->end_sim)
		printf("%ld\t%d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&philo->main_ptr->lock);
}

int	watch_fork(t_fork *fork, t_philo *philo)
{
	int		ret;

	ret = 0;
	pthread_mutex_lock(&fork->lock);
	if (!fork->is_taken)
	{
		fork->is_taken = true;
		print_msg("has taken a fork", philo);
		ret = 1;
	}
	pthread_mutex_unlock(&fork->lock);
	return (ret);
}

void	put_back_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->lock);
	philo->l_fork->is_taken = false;
	pthread_mutex_unlock(&philo->l_fork->lock);
	pthread_mutex_lock(&philo->r_fork->lock);
	philo->r_fork->is_taken = false;
	pthread_mutex_unlock(&philo->r_fork->lock);
}

void	eat(t_philo *philo)
{
	while (watch_fork(philo->l_fork, philo) != 1)
		;
	while (watch_fork(philo->r_fork, philo) != 1)
		;
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->lock);
	philo->time_since_eat = get_time();
	pthread_mutex_unlock(&philo->lock);
	ft_sleep(philo->main_ptr->time_to_eat);
	put_back_forks(philo);
	pthread_mutex_lock(&philo->lock);
	if (philo->nb_eat > 0)
		philo->nb_eat--;
	pthread_mutex_unlock(&philo->lock);
}
