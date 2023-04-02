/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:22:51 by msamhaou          #+#    #+#             */
/*   Updated: 2023/04/02 11:40:52 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TAKE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define NOMORE 5
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_envment
{
	int				num_of_philo;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				done_eat;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	w_mutex;
	pthread_mutex_t	d_mutex;
}	t_envment;

typedef struct s_phil
{
	pthread_t		thread;
	int				pos;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	int				is_eating;
	size_t			eat_limit;
	t_envment		*envm;
}	t_phil;

int		ft_check_arg(char **av);
int		ft_init(t_envment *envm, char **av, int ac);
t_phil	**ft_philo_init(t_envment *envm);
void	ft_eat(t_phil *philo);
int		ft_check_death(t_phil **philo, t_envment *envm);
int		ft_check_meal(t_phil *philo);
int		ft_thread_create(t_phil **philo, t_envment *envm);
void	*routine(void *parg);
int		ft_print_message(t_phil *philo, t_envment *envment, int type);
size_t	ft_get_time(void);
int		ft_atoi(char *str);
void	ft_free_philo(t_phil **philo, int pos);
void	ft_usleep(size_t ms);
int		ft_thread_join(t_phil **philo);
void	ft_free_end(t_phil **philo, t_envment *envm);

#endif