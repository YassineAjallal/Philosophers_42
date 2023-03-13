/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:42:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/13 17:41:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_details *thread)
{
	int nb_philo;

	pthread_mutex_lock(&thread->philo->mutex_list->m_nb_philo);
	nb_philo = thread->philo->nb_philo;
	pthread_mutex_unlock(&thread->philo->mutex_list->m_nb_philo);
	if (nb_philo == 1)
	{
		pthread_mutex_lock(&thread->philo->fork[thread->id]);
		pthread_mutex_lock(&thread->philo->mutex_list->m_time_start);
		printf("%lld %d has taken a fork\n",
			get_time() - thread->philo->time_start, thread->id + 1);
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_start);
		pthread_mutex_lock(&thread->philo->mutex_list->m_time_die);
		own_sleep(thread->philo->time_die);
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_die);
		thread->is_died = 1;
		pthread_mutex_unlock(&thread->philo->fork[thread->id]);
		return (0);
	}
	return (1);
}

int	mutex_lock(t_details *thread)
{
	if (!one_philo(thread))
		return (0);

	pthread_mutex_lock(&thread->philo->fork[thread->id]);
	pthread_mutex_lock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);

	pthread_mutex_lock(&thread->philo->mutex_list->m_time_die);
	if (get_time() - thread->last_eat_time >= thread->philo->time_die)
	{
		thread->is_died = 1;
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_die);
		return (0);
	}
	pthread_mutex_unlock(&thread->philo->mutex_list->m_time_die);

	pthread_mutex_lock(&thread->philo->mutex_list->m_time_start);
	printf("%lld %d has taken a fork\n",
		get_time() - thread->philo->time_start, thread->id + 1);
	printf("%lld %d has taken a fork\n",
		get_time() - thread->philo->time_start, thread->id + 1);
	printf("%lld %d is eating\n",
		get_time() - thread->philo->time_start, thread->id + 1);
	pthread_mutex_unlock(&thread->philo->mutex_list->m_time_start);

	thread->last_eat_time = get_time();

	pthread_mutex_lock(&thread->philo->mutex_list->m_time_eat);
	own_sleep(thread->philo->time_eat);
	pthread_mutex_unlock(&thread->philo->mutex_list->m_time_eat);

	thread->nb_eat++;
	pthread_mutex_unlock(&thread->philo->fork[thread->id]);
	pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);
	return (1);
}
