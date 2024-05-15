/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:10:17 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/15 14:07:00 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nb;
	long	i;
	long	sign;

	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb != (nb * 10 + (str[i] - 48)) / 10)
			return (0);
		nb = (nb * 10) + (str[i++] - 48);
	}
	return (nb * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000000) + (long)tv.tv_usec);
}

inline void	ft_sleep(long us)
{
	long	start;

	start = get_time();
	usleep(us * 0.8);
	while ((get_time() - start) < us)
		usleep(30);
}

void	free_main(t_main *main, char *msg, bool end)
{
	int		i;
	long	nb_p;

	if (msg)
		printf("%s\n", msg);
	i = -1;
	nb_p = main->nb_philo;
	while (++i < nb_p && end)
		pthread_join(main->philos_threads[i], NULL);
	i = -1;
	while (++i < nb_p && end)
	{
		pthread_mutex_destroy(&main->philo_info[i].lock);
		pthread_mutex_destroy(&main->forks[i].lock);
	}
	if (main->philo_info)
		free(main->philo_info);
	if (main->forks)
		free(main->forks);
	if (main->philos_threads)
		free(main->philos_threads);
	if (end)
		pthread_mutex_destroy(&main->lock);
	if (end)
		pthread_mutex_destroy(&main->write_lock);
}

void	mid_loop_free(t_main *main, int i)
{
	int	j;

	j = i;
	set_bool(&main->end_sim, true, &main->lock);
	while (i >= 0)
	{
		pthread_join(main->philos_threads[i], NULL);
		i--;
	}
	i = j;
	while (i >= 0)
	{
		pthread_mutex_destroy(&main->philo_info[i].lock);
		pthread_mutex_destroy(&main->forks[i].lock);
		i--;
	}
	free_main(main, "pthread function failed", false);
}
