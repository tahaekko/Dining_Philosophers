/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 05:32:51 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 11:40:33 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
