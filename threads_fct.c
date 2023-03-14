/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:35:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/14 17:02:46 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->m_is_dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->m_is_finish, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->m_last_eat_time, NULL) != 0)
		return (0);
	return (1);
}

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
		threads[i].philo->is_died = 0;
		threads[i].is_finish = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	stop_threads(t_details *threads)
{
	int	i;

	i = 0;
	while (i < threads[0].philo->nb_philo)
	{
		pthread_mutex_lock(&threads[i].philo->m_last_eat_time);
		if (get_time() - threads[i].last_eat_time >= threads[i].philo->time_die)
		{
			printf("%lld %d died\n",
				get_time() - threads[i].philo->time_start, threads[i].id + 1);
			pthread_mutex_lock(&threads[i].philo->m_is_dead);
			threads[i].philo->is_died = 1;
			pthread_mutex_unlock(&threads[i].philo->m_is_dead);
			pthread_mutex_unlock(&threads[i].philo->m_last_eat_time);
			return (0);
		}
		else if (ft_check_nb_eat(threads))
			return (0);
		pthread_mutex_unlock(&threads[i].philo->m_last_eat_time);
		i++;
		if (i == threads[0].philo->nb_philo)
			i = 0;
	}
	return (1);
}
