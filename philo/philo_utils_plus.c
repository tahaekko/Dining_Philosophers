/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:37:53 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 09:51:18 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
