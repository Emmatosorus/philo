/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:33:08 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/15 11:28:02 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_main(t_main *main)
{
	main->philo_info = NULL;
	main->philos_threads = NULL;
	main->forks = NULL;
	main->end_sim = false;
	main->start_watching = false;
	main->threads_ready = 0;
	main->timestamp = 0;
	main->nb_meals = -1;
}

int	get_value(long *var, char *nb, bool philo)
{
	if (philo)
		*var = ft_atoi(nb);
	else
		*var = ft_atoi(nb) * 1000;
	if (*var < 1 || (*var == 0 && nb[0] != '0') || *var > INT_MAX)
		return (1);
	return (0);
}

int	convert_input(char **av, t_main *main)
{
	init_main(main);
	if (get_value(&main->nb_philo, av[1], true) != 0)
		return (1);
	if (get_value(&main->time_to_die, av[2], false) != 0)
		return (1);
	if (get_value(&main->time_to_eat, av[3], false) != 0)
		return (1);
	if (get_value(&main->time_to_sleep, av[4], false) != 0)
		return (1);
	if (av[5] && get_value(&main->nb_meals, av[5], true) != 0)
		return (1);
	return (0);
}
