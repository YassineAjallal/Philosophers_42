/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:06:59 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/12 14:22:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, char **av)
{
	philo->time_start = get_time();
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->nb_times = ft_atoi(av[5]);
	else
		philo->nb_times = -1;
}

int	check_arg(t_philo *philo)
{
	if (philo->nb_philo <= 0)
		return (0);
	if (philo->time_die <= 0 || philo->time_eat <= 0
		|| philo->time_sleep <= 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	if (ac != 6 && ac != 5)
	{
		printf("Error\nBad usage\n");
		return (0);
	}
	init_philo(philo, av);
	if (!check_arg(philo))
		return (0);
	create_thread(philo);
	return (0);
}
