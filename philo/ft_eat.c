/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:21:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/01 11:57:25 by msamhaou         ###   ########.fr       */
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
	ft_usleep(philo->envm->time_to_eat);
	pthread_mutex_unlock(&philo->envm->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->envm->forks[philo->right_fork]);
}

int	ft_mutex_init(t_envment *envm)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&envm->w_mutex, NULL) != 0
		|| pthread_mutex_init(&envm->d_mutex, NULL) != 0)
		return (1);
	envm->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* envm->num_of_philo);
	if (!envm->forks)
		return (1);
	while (i < envm->num_of_philo)
	{
		if (pthread_mutex_init(&envm->forks[i++], NULL) != 0)
			return (1);
	}
	return (0);
}
