/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/13 17:58:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation_fct(void *p)
{
	t_details	*thread;

	thread = (t_details *)p;
	while (1)
	{
		if (!mutex_lock(thread))
			break ;
		pthread_mutex_lock(&thread->philo->mutex_list->m_nb_times);
		if (thread->nb_eat == thread->philo->nb_times)
		{
			thread->is_finish = 1;
			pthread_mutex_unlock(&thread->philo->mutex_list->m_nb_times);
			break ;
		}
		pthread_mutex_unlock(&thread->philo->mutex_list->m_nb_times);
		pthread_mutex_lock(&thread->philo->mutex_list->m_time_start);
		printf("%lld %d is sleeping\n",
			get_time() - thread->philo->time_start, thread->id + 1);
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_start);
		
		pthread_mutex_lock(&thread->philo->mutex_list->m_time_sleep);
		own_sleep(thread->philo->time_sleep);
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_sleep);

		pthread_mutex_lock(&thread->philo->mutex_list->m_time_start);
		printf("%lld %d is thinking\n",
			get_time() - thread->philo->time_start, thread->id + 1);
		pthread_mutex_unlock(&thread->philo->mutex_list->m_time_start);
		own_sleep(10);
	}
	return (NULL);
}

int	create_thread(t_philo *philo)
{
	int			i;
	t_details	*threads;

	i = -1;
	threads = malloc(sizeof(t_details) * philo->nb_philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	philo->mutex_list = malloc(sizeof(t_mutex_list));
	if (!threads || !philo->fork || !philo->mutex_list)
		return (0);
	if (!init_threads(philo, threads))
		return (0);
	if (!init_mutex(philo->mutex_list))
		return (0);
	while (++i < philo->nb_philo)
	{
		if (pthread_create(&threads[i].thread, NULL,
				simulation_fct, &threads[i]) != 0)
			return (0);
	}
	if (!stop_threads(philo, threads))
		return (0);
	i = -1;
	while (++i < philo->nb_philo)
	{	
		if (pthread_join(threads[i].thread, NULL) != 0)
			return (0);
	}
	return (1);
}
