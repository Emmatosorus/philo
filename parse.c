/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:33:08 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/06 17:35:01 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_main(t_main *main)
{
	main->philos = NULL;
	main->forks = NULL;
	main->end_sim = false;
	main->start_watching = false;
	main->threads_ready = 0;
	main->timestamp = 0;
}

int	get_value(long *var, char *nb)
{
	*var = ft_atoi(nb);
	if (*var < 0 || (*var == 0 && nb[0] != '0'))
		return (1);
	return (0);
}

int	convert_input(char **av, t_main *main)
{
	init_main(main);
	if (get_value(&main->nb_philo, av[1]) != 0)
		return (1);
	if (get_value(&main->time_to_die, av[2]) != 0)
		return (1);
	if (get_value(&main->time_to_eat, av[3]) != 0)
		return (1);
	if (get_value(&main->time_to_sleep, av[4]) != 0)
		return (1);
	if (av[5] && get_value(&main->nb_meals, av[5]) != 0)
		return (1);
	return (0);
}