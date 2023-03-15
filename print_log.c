/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:36:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/15 18:15:52 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(t_details *thread, char *log)
{
	pthread_mutex_lock(&thread->philo->m_is_dead);
	if (thread->philo->is_died != 1)
	{
		pthread_mutex_lock(&thread->philo->m_print);
		printf("%lld %d %s\n", get_time() - thread->philo->time_start, thread->id + 1, log);
		pthread_mutex_unlock(&thread->philo->m_print);
	}
	pthread_mutex_unlock(&thread->philo->m_is_dead);
}