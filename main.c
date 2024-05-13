/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/13 09:33:45 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_vars(t_main main)
{
	printf("Number of philosophers : %ld\n", main.nb_philo);
	printf("Time until death : %ld\n", main.time_to_die);
	printf("Time to eat : %ld\n", main.time_to_eat);
	printf("Time to sleep : %ld\n", main.time_to_sleep);
	printf("Number of meals : %ld\n", main.nb_meals);
}

void	wait_for_launch(t_main *main)
{
	while (!get_bool(&main->start_watching, &main->lock))
	{
		if (get_long(&main->threads_ready, &main->lock) == get_long(&main->nb_philo, &main->lock))
		{
			set_long(&main->timestamp, get_time(), &main->lock);
			set_bool(&main->start_watching, true, &main->lock);
		}
	}
}

void	watch(t_main *main)
{
	int 	i;
	long	last_eat;
	long	death_time;
	long	finished;

	death_time = get_long(&main->time_to_die, &main->lock);
	finished = 0;
	while (!get_bool(&main->end_sim, &main->lock))
	{
		i = -1;
		while (++i < main->nb_philo)
		{
			if (get_long(&main->nb_meals, &main->lock) != -1 && get_long(&main->philo_info[i].nb_eat, &main->philo_info[i].lock) > 0)
				finished++;
			last_eat = get_long(&main->philo_info[i].time_since_eat, &main->philo_info[i].lock);
			if (get_time() - last_eat > death_time || finished == get_long(&main->nb_philo, &main->lock))
			{
				printf("%ld\t%ld has died\n", get_time(), get_long(&main->philo_info[i].id, &main->philo_info[i].lock));
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
	print_vars(main);
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
	return (0);
}
