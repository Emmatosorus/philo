/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/06 17:35:46 by epolitze         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 5 || ac > 6 || convert_input(av, &main) != 0)
	{
		printf("Error\nIncorrect arguments!\n");
		return (1);
	}
	print_vars(main);
	
}
