/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:06:59 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/19 13:37:42 by yajallal         ###   ########.fr       */
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
		return (0);
	}
	if (!check_philo(philo, av))
		return (0);
	create_thread(philo);
	return (0);
}
