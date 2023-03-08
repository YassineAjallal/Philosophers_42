/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:42:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/08 12:17:31 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mutex_lock(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->fork[thread->id]);
	if (current_time() - thread->last_eat_time > thread->philo->time_die || thread->philo->nb_philo == 1)
	{
		// pthread_mutex_lock(&thread->philo->print_die);
		if (*(thread->is_died) != 1)
		{
			*(thread->is_died) = 1;
			printf("%lld %d is died\n", current_time() - thread->philo->time_start ,thread->id + 1);
			pthread_mutex_unlock(&thread->philo->fork[thread->id]);
			pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
		}
		// pthread_mutex_unlock(&thread->philo->print_die);
		return (0);
	}
	pthread_mutex_lock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
	printf("%lld %d has taken a fork\n", current_time() - thread->philo->time_start ,thread->id + 1);
	printf("%lld %d is eating\n", current_time() - thread->philo->time_start ,thread->id + 1);
	own_sleep(thread->philo->time_eat);
	thread->nb_eat++;
	thread->last_eat_time = current_time();
	pthread_mutex_unlock(&thread->philo->fork[thread->id]);
	pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
	return (1);
}