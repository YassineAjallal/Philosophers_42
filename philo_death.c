/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:29:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/14 16:42:49 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_death(t_details *thread)
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
