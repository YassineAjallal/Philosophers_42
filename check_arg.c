/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:14:37 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/19 13:34:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check is thre is a digit in arguments
int check_arg(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);	
}

// fill the philo struct
int	init_philo(t_philo *philo, char **av)
{
	if (!check_arg(av))
		return (0);
	philo->time_start = get_time();
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->nb_times = ft_atoi(av[5]);
	else
		philo->nb_times = -1;
	return (1);
}

// check if all argument a non null positive digits
int	check_philo(t_philo *philo, char **av)
{
	if (!init_philo(philo, av))
		return (0);
	if (philo->nb_philo <= 0)
		return (0);
	if (philo->time_die <= 0 || philo->time_eat <= 0
		|| philo->time_sleep <= 0)
		return (0);
	return (1);
}