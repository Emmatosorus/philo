/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/04/30 17:52:14 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	printf("Lemme think!\n");
	sleep(2);
	printf("Ending life\n");
	return (NULL);
}

void	create_philosopher(char **av, int philo_id)
{
	t_philo	philo;

	philo.id = philo_id;
	philo.fork = true;
	philo.eat_time = 0;
	philo.sleep_time = 0;
//	pthread_create(&philo, NULL, &routine, NULL);
//	pthread_join(philo, NULL);
}

int	main(int ac, char **av)
{
	int	nb_philo;
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	nb_philo = ft_atoi(av[1]);
	if (nb_philo > 201 || nb_philo < 1)
		return (1);
	i = 0;
	while (i++ <= nb_philo)
		create_philosopher(av, i);
	return (0);
}
