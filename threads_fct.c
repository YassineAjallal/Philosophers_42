/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:35:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 18:58:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philo *philo, t_details *threads)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		threads[i].id = i;
		threads[i].last_eat_time = get_time();
		threads[i].nb_eat = 0;
		threads[i].philo = philo;
		threads[i].is_died = 0;
		threads[i].is_finish = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	stop_threads(t_philo *philo, t_details *threads)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (threads[i].is_died == 1)
		{
			printf("%lld %d is died\n",
				get_time() - threads[i].philo->time_start, threads[i].id + 1);
			return (0);
		}
		else if (ft_check_nb_eat(threads, philo->nb_philo))
			return (0);
		i++;
		if (i == philo->nb_philo)
			i = 0;
	}
	return (1);
}
