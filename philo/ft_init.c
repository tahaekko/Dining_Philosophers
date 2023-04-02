/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 09:49:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 14:49:04 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_mutex_init(t_envment *envm)
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

int	ft_init(t_envment *envm, char **av, int ac)
{
	envm->num_of_philo = ft_atoi(av[1]);
	envm->time_to_die = ft_atoi(av[2]);
	envm->time_to_eat = ft_atoi(av[3]);
	envm->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		envm->must_eat = ft_atoi(av[5]);
	envm->done_eat = 0;
	envm->alive = 1;
	if (ft_mutex_init(envm) != 0)
		return (1);
	return (0);
}

static t_phil	**ft_philo_malloc(t_envment *envm)
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

t_phil	**ft_philo_init(t_envment *envm)
{
	int		i;
	t_phil	**philo;

	philo = ft_philo_malloc(envm);
	if (!philo)
		return (NULL);
	i = 0;
	while (philo[i])
	{
		philo[i]->pos = i;
		philo[i]->left_fork = i;
		philo[i]->right_fork = (i + 1) % envm->num_of_philo;
		philo[i]->eat_count = 0;
		philo[i]->envm = envm;
		philo[i]->is_eating = 0;
		i++;
	}
	return (philo);
}
