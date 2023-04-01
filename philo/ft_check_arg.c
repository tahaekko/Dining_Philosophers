/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 07:52:50 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/01 13:07:12 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	if (str[i] == '0')
		return (1);
	if (str[i] == '+')
			i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_arg(char **av)
{
	int	i;

	i = 1;
	while (av[i])
		if (ft_check_str(av[i++]) == 1)
			return (1);
	return (0);
}
