/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:22:55 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 14:23:13 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(const long *value, pthread_mutex_t *lock)
{
	long	var;

	pthread_mutex_lock(lock);
	var = *value;
	pthread_mutex_unlock(lock);
	return (var);
}

bool	get_bool(const bool *value, pthread_mutex_t *lock)
{
	bool	var;

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
