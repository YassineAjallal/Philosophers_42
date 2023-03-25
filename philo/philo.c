/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:06:59 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/24 17:40:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	if (ac != 6 && ac != 5)
	{
		printf("Error\nBad usage\n");
		free(philo);
		return (0);
	}
	if (!check_philo(philo, av))
	{
		free(philo);
		return (0);
	}
	ft_thread(philo);
	mutex_destroy(philo);
	free(philo->fork);
	free(philo);
	return (0);
}
