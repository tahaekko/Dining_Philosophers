/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:37:53 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/01 11:09:58 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_phil	**ft_philo_malloc(t_envment *envm)
{
	t_phil	**philo;
	int		i;

	philo = (t_phil **)malloc(sizeof(t_phil *) * (envm->num_of_philo + 1));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < envm->num_of_philo)
	{
		philo[i] = (t_phil *)malloc(sizeof(t_phil));
		if (!philo[i])
		{
			ft_free_philo(philo, i);
			return (NULL);
		}
		i++;
	}
	philo[i] = NULL;
	return (philo);
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

int	ft_check_death(t_phil **philo, t_envment *envm)
{
	int	i;

	while (1)
	{
		i = 0;
		while (philo[i])
		{
			pthread_mutex_lock(&envm->d_mutex);
			if (envm->done_eat)
			{
				pthread_mutex_unlock(&envm->d_mutex);
				return (0);
			}
			if ((ft_get_time() - philo[i]->eat_limit) > (size_t)envm->time_to_die )
			{
				pthread_mutex_lock(&envm->w_mutex);
				printf("%zu %d died\n", ft_get_time() - envm->start_time, philo[i]->pos + 1);
				pthread_mutex_unlock(&envm->d_mutex);
				return (1);
			}
			i++;
			pthread_mutex_unlock(&envm->d_mutex);
		}
	}
	return (0);
}

int	ft_thread_join(t_phil **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		pthread_join(philo[i++]->thread, NULL);
	}
	return (0);
}
