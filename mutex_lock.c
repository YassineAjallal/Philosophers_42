/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:42:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 17:14:56 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mutex_lock(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->fork[thread->id]);
	if (thread->philo->nb_philo == 1)
	{
		printf("%lld %d has taken a fork\n", get_time() - thread->philo->time_start ,thread->id + 1);
		own_sleep(thread->philo->time_die);
		printf("%lld %d is died\n", get_time() - thread->philo->time_start ,thread->id + 1);
		*(thread->is_died) = 1;
		pthread_mutex_unlock(&thread->philo->fork[thread->id]);
		return (0);
	}
	else if (get_time() - thread->last_eat_time >= thread->philo->time_die)
	{
			own_sleep(10);
			pthread_mutex_lock(&thread->philo->print_die);
			printf("%lld %d is died\n", get_time() - thread->philo->time_start ,thread->id + 1);
			*(thread->is_died) = 1;
			pthread_mutex_unlock(&thread->philo->print_die);
			pthread_mutex_unlock(&thread->philo->fork[thread->id]);
			return (0);
	}
	pthread_mutex_lock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
	if (*(thread->is_died) == 1)
			return (0);
	printf("%lld %d has taken a fork\n", get_time() - thread->philo->time_start ,thread->id + 1);
	printf("%lld %d is eating\n", get_time() - thread->philo->time_start ,thread->id + 1);
	thread->last_eat_time = get_time();
	own_sleep(thread->philo->time_eat);
	thread->nb_eat++;
	pthread_mutex_unlock(&thread->philo->fork[thread->id]);
	pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
	return (1);
}