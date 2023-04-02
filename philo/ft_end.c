/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:47:46 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 12:03:27 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_philo(t_phil **philo, int pos)
{
	while (pos--)
		free(philo[pos]);
	free(philo);
}

static void	ft_free_all(t_phil **philo)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	ft_free_end(t_phil **philo, t_envment *envm)
{
	int	i;

	i = 0;
	if (envm->forks)
		free(envm->forks);
	if (philo)
		ft_free_all(philo);
	pthread_mutex_destroy(&envm->d_mutex);
	pthread_mutex_destroy(&envm->w_mutex);
}
