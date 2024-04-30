/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:11 by epolitze          #+#    #+#             */
/*   Updated: 2024/04/30 17:04:53 by epolitze         ###   ########.fr       */
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

//void	create_philosopher()
//{
//
//}

int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;
	int			nb_philo;

	if (ac < 5 || ac > 6)
		return (1);
	nb_philo = ft_atoi(av[1]);
	if (nb_philo > 201 || nb_philo < 1)
		return (1);
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
