/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:29:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/15 18:38:11 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->m_is_dead);
	if (thread->philo->is_died == 1)
	{
		pthread_mutex_unlock(&thread->philo->m_is_dead);
		return (0);
	}
	pthread_mutex_unlock(&thread->philo->m_is_dead);
	return (1);
}

int	eat_checker(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->m_nb_eat);
	if (thread->nb_eat == thread->philo->nb_times)
	{
		pthread_mutex_lock(&thread->philo->m_is_finish);
		thread->is_finish = 1;
		pthread_mutex_unlock(&thread->philo->m_is_finish);
		pthread_mutex_unlock(&thread->philo->m_nb_eat);
		return (0);
	}
	pthread_mutex_unlock(&thread->philo->m_nb_eat);
	return (1);
}

int	check_nb_eat(t_details *threads)
{
	int	i;
	i = 0;
	while (i < threads->philo->nb_philo)
	{
		pthread_mutex_lock(&threads[i].philo->m_is_finish);
		if (threads[i].is_finish != 1)
		
		{
			pthread_mutex_unlock(&threads[i].philo->m_is_finish);
			return (0);
		}
		pthread_mutex_unlock(&threads[i].philo->m_is_finish);
		i++;
	}
	return (1);
}