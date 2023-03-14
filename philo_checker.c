/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:29:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/14 17:03:02 by yajallal         ###   ########.fr       */
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
	if (thread->nb_eat == thread->philo->nb_times)
	{
		pthread_mutex_lock(&thread->philo->m_is_finish);
		thread->is_finish = 1;
		pthread_mutex_unlock(&thread->philo->m_is_finish);
		return (0);
	}
	return (1);
}
