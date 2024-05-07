/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/07 16:26:51 by epolitze         ###   ########.fr       */
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
	while (!main->start_watching)
	{
		pthread_mutex_lock(&main->lock);
		if (main->threads_ready == main->nb_philo)
			main->start_watching = true;
		pthread_mutex_unlock(&main->lock);
	}
}

void	watch(t_main *main)
{
	int 	i;
	long	last_eat;
	long	death_time;
	long	finished;

	get_long_main(main, &death_time);
	finished = 0;
	while (is_end(main) != 1)
	{
		i = -1;
		while (++i < main->nb_philo)
		{
			if (main->nb_meals != -1 && finished_eating(&main->philo_info[i]) == 0)
				finished++;
			get_long_philo(&main->philo_info[i], &last_eat);
			if (get_time() - last_eat > death_time || finished == main->nb_philo)
			{
				printf("%ld\t%d has died\n", get_time(), main->philo_info[i].id);
				pthread_mutex_lock(&main->lock);
				main->end_sim = true;
				pthread_mutex_unlock(&main->lock);
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
