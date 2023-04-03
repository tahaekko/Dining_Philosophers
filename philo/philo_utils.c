/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:24:44 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 15:54:44 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_message(t_phil *philo, t_envment *envment, int type)
{
	pthread_mutex_lock(&envment->d_mutex);
	if (envment->alive)
	{
		pthread_mutex_lock(&envment->w_mutex);
		if (type == TAKE)
			printf("%zu %d has taken a fork\n", ft_get_time()
				- philo->envm->start_time, philo->pos + 1);
		else if (type == EAT)
			printf("%zu %d is eating\n", ft_get_time()
				- philo->envm->start_time, philo->pos + 1);
		else if (type == SLEEP)
			printf("%zu %d is sleeping\n", ft_get_time()
				- philo->envm->start_time, philo->pos + 1);
		else if (type == THINK)
			printf("%zu %d is thinking\n", ft_get_time()
				- philo->envm->start_time, philo->pos + 1);
		pthread_mutex_unlock(&envment->w_mutex);
	}
	pthread_mutex_unlock(&envment->d_mutex);
	return (0);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	start_time;

	start_time = ft_get_time();
	usleep((ms - 20) * 1000);
	while ((ft_get_time() - start_time) < ms)
		;
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res *= 10;
		res += str[i++] - 48;
	}
	return (res);
}
