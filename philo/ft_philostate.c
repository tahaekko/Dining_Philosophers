/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philostate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:37:53 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/03 08:57:31 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_phil *philo)
{
	pthread_mutex_lock(&philo->envm->forks[philo->left_fork]);
	ft_print_message(philo, philo->envm, TAKE);
	pthread_mutex_lock(&philo->envm->forks[philo->right_fork]);
	ft_print_message(philo, philo->envm, TAKE);
	ft_print_message(philo, philo->envm, EAT);
}

static int	ft_check_death_plus(t_phil *philo, t_envment *envm)
{
	if ((ft_get_time() - philo->eat_limit) > envm->time_to_die)
	{
		pthread_mutex_lock(&envm->w_mutex);
		envm->alive = 0;
		printf("%zu %d died\n", ft_get_time()
			- envm->start_time, philo->pos + 1);
		pthread_mutex_unlock(&envm->w_mutex);
		pthread_mutex_unlock(&envm->d_mutex);
		return (1);
	}
	return (0);
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
			if (ft_check_death_plus(philo[i], envm))
			{
				usleep(1000);
				return (1);
			}
			pthread_mutex_unlock(&envm->d_mutex);
			i++;
		}
	}
	return (0);
}

int	ft_check_meal(t_phil *philo)
{
	pthread_mutex_lock(&philo->envm->d_mutex);
	philo->eat_count += 1;
	if (philo->envm->must_eat > 0)
	{
		if (philo->eat_count >= philo->envm->must_eat)
		{
			philo->envm->done_eat = 1;
			pthread_mutex_unlock(&philo->envm->d_mutex);
			ft_print_message(philo, philo->envm, SLEEP);
			return (1);
		}
	}
	philo->eat_limit = ft_get_time();
	pthread_mutex_unlock(&philo->envm->d_mutex);
	ft_print_message(philo, philo->envm, SLEEP);
	ft_usleep(philo->envm->time_to_sleep);
	ft_print_message(philo, philo->envm, THINK);
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
