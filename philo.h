/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:38:14 by epolitze          #+#    #+#             */
/*   Updated: 2024/04/30 17:50:41 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_GIT_PHILO_H
#define PHILO_GIT_PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int	ft_atoi(const char *str);

typedef struct s_philo
{
	int		id;
	bool	fork;
	int		sleep_time;
	int		eat_time;
}			t_philo;

#endif //PHILO_GIT_PHILO_H
