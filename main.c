/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/14 09:33:28 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_launch(t_main *main)
{
	while (!get_bool(&main->start_watching, &main->lock))
	{
		if (get_long(&main->threads_ready, &main->lock) == \
			get_long(&main->nb_philo, &main->lock))
		{
			set_long(&main->timestamp, get_time(), &main->lock);
			set_bool(&main->start_watching, true, &main->lock);
		}
	}
}

bool	philo_died(t_main *main, int i, long death_time)
{
	if (get_time() - get_long(&main->philo_info[i].time_since_eat, \
				&main->philo_info[i].lock) > death_time)
	{
		set_bool(&main->end_sim, true, &main->lock);
		print_msg("has died", &main->philo_info[i], true);
		return (true);
	}
	return (false);
}

void	watch(t_main *main)
{
	int		i;
	long	death_time;
	long	finished;

	death_time = main->time_to_die;
	finished = 0;
	while (!get_bool(&main->end_sim, &main->lock))
	{
		i = -1;
		while (++i < main->nb_philo)
		{
			if (main->nb_meals != -1 && get_long(&main->philo_info[i].nb_eat, \
				&main->philo_info[i].lock) <= 0)
				finished++;
			if (philo_died(main, i, death_time))
				break ;
			else if (main->nb_meals != -1 && finished == main->nb_philo)
			{
				set_bool(&main->end_sim, true, &main->lock);
				break ;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 5 || ac > 6 || convert_input(av, &main) != 0)
	{
		printf("Error\nIncorrect arguments!\n");
		return (1);
	}
	if (allocate_philosophers(&main) != 0)
	{
		printf("Error\nMalloc has failed\n");
		return (1);
	}
	if (create_philosophers(&main) != 0)
	{
		free_main(&main, "Error\nCouldn't create thread");
		return (1);
	}
	wait_for_launch(&main);
	watch(&main);
	free_main(&main, NULL);
	return (0);
}
