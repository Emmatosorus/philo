/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:10:17 by epolitze          #+#    #+#             */
/*   Updated: 2024/05/07 16:12:09 by epolitze         ###   ########.fr       */
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

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (s);
}

long	get_time()
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_usec / 1000);
}

void	ft_sleep(long ms)
{
	long	start;

	start = get_time();
	ms *= 1000;
	while (get_time() - start < ms)
		usleep(ms / 10);
}

void	free_main(t_main *main, char *msg)
{
	int	i;

	if (msg)
		printf("%s\n", msg);
	i = -1;
	while (++i < main->nb_philo)
		pthread_join(main->philos_threads[i], NULL);
	i = -1;
	while (++i < main->nb_philo)
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
	pthread_mutex_destroy(&main->lock);
}