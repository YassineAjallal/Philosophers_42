/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:34:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/23 22:32:33 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&philo->m_is_dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->m_eat, NULL) != 0)
		return (0);
	return (1);
}

// handle eating
int	mutex_lock(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->fork[thread->id]);
	print_log(thread, "has taken a fork");
	pthread_mutex_lock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);
	print_log(thread, "has taken a fork");
	print_log(thread, "is eating");
	pthread_mutex_lock(&thread->philo->m_eat);
	thread->last_eat_time = get_time();
	thread->nb_eat++;
	pthread_mutex_unlock(&thread->philo->m_eat);
	own_sleep(thread->philo->time_eat);
	pthread_mutex_unlock(&thread->philo->fork[thread->id]);
	pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);
	return (1);
}

void	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->m_is_dead);
	pthread_mutex_destroy(&philo->m_eat);
}
