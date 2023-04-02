/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:24:44 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 11:45:09 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_message(t_phil *philo, t_envment *envment, int type)
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
			if ((ft_get_time() - philo[i]->eat_limit) > envm->time_to_die )
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

int	ft_check_meal(t_phil *philo)
{
	pthread_mutex_lock(&philo->envm->d_mutex);
	philo->eat_count += 1;
	if (philo->envm->must_eat > 0)
	{
		if (philo->eat_count >= philo->envm->must_eat)
		{
			philo->envm->done_eat = 1;
			ft_print_message(philo, philo->envm, SLEEP);
			pthread_mutex_unlock(&philo->envm->d_mutex);
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
void	*routine(void *parg)
{
	t_phil	*philo;

	philo = (t_phil *)parg;
	if ((philo->pos % 2) != 0)
		usleep(400);
	while (1)
	{
		ft_eat(philo);
		ft_usleep(philo->envm->time_to_eat);
		pthread_mutex_unlock(&philo->envm->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->envm->forks[philo->right_fork]);
		if (ft_check_meal(philo))
			return (NULL);
	}
	return (NULL);
}

int	ft_thread_create(t_phil **philo, t_envment *envm)
{
	int	i;

	i = 0;
	envm->start_time = ft_get_time();
	while (philo[i])
	{
		philo[i]->eat_limit = ft_get_time();
		if (pthread_create(&philo[i]->thread, NULL, &routine, philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

