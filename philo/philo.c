/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 05:32:51 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/01 12:56:40 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init(t_envment *envm, char **av, int ac)
{
	envm->num_of_philo = ft_atoi(av[1]);
	envm->time_to_die = ft_atoi(av[2]);
	envm->time_to_eat = ft_atoi(av[3]);
	envm->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		envm->must_eat = ft_atoi(av[5]);
	envm->done_eat = 0;
	if (ft_mutex_init(envm) != 0)
		return (1);
	return (0);
}

static t_phil	**ft_philo_init(t_envment *envm)
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

static void	*routine(void *parg)
{
	t_phil	*philo;

	philo = (t_phil *)parg;
	if ((philo->pos % 2) != 0)
		usleep(500);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&philo->envm->d_mutex);
		philo->eat_limit = ft_get_time();
		philo->eat_count += 1;
		if (philo->envm->must_eat > 0)
		{
			if (philo->eat_count > philo->envm->must_eat)
			{
				philo->envm->done_eat = 1;
				ft_print_message(philo, philo->envm, SLEEP);
				pthread_mutex_unlock(&philo->envm->d_mutex);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->envm->d_mutex);
		ft_print_message(philo, philo->envm, SLEEP);
		ft_usleep(philo->envm->time_to_sleep);
		ft_print_message(philo, philo->envm, THINK);
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
		return (0);
	ft_thread_join(philo);
	ft_free_end(philo, envment);
	return (0);
}
