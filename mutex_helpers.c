/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:22:55 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 09:26:47 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(long *value, pthread_mutex_t *lock)
{
	long	nb;

	nb = 0;
	pthread_mutex_lock(lock);
	nb = *value;
	pthread_mutex_unlock(lock);
	return (nb);
}

bool	get_bool(bool *value, pthread_mutex_t *lock)
{
	bool	var;

	var = false;
	pthread_mutex_lock(lock);
	var = *value;
	pthread_mutex_unlock(lock);
	return (var);
}

void	set_bool(bool *var, bool value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*var = value;
	pthread_mutex_unlock(lock);
}

void	set_long(long *var, long value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*var = value;
	pthread_mutex_unlock(lock);
}