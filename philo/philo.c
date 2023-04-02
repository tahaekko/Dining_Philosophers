/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 05:32:51 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 12:03:00 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *parg)
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

static int	ft_thread_create(t_phil **philo, t_envment *envm)
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

int	main(int ac, char **av)
{
	t_envment	*envment;
	t_phil		**philo;

	envment = (t_envment *)malloc(sizeof(t_envment));
	if (ac < 5 || ac > 6)
		return (1);
	philo = NULL;
	if (ft_check_arg(av))
		return (1);
	if (ft_init(envment, av, ac))
		return (ft_free_end(philo, envment), 1);
	philo = ft_philo_init(envment);
	if (!philo)
		return (ft_free_end(philo, envment), 1);
	if (ft_thread_create(philo, envment) != 0)
		return (ft_free_end(philo, envment), 1);
	if (ft_check_death(philo, envment) == 1)
		return (ft_free_end(philo, envment), 0);
	ft_thread_join(philo);
	ft_free_end(philo, envment);
	return (0);
}
