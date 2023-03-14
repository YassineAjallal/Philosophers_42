/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/14 16:39:51 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation_fct(void *p)
{
	t_details	*thread;

	thread = (t_details *)p;
	if ((thread->id + 1) % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (!philo_death(thread))
			break ;
		if (!mutex_lock(thread))
			break ;
		if (thread->nb_eat == thread->philo->nb_times)
		{
			pthread_mutex_lock(&thread->philo->m_is_finish);
			thread->is_finish = 1;
			pthread_mutex_unlock(&thread->philo->m_is_finish);
			break ;
		}
		printf("%lld %d is sleeping\n",
			get_time() - thread->philo->time_start, thread->id + 1);
		own_sleep(thread->philo->time_sleep);
		printf("%lld %d is thinking\n",
			get_time() - thread->philo->time_start, thread->id + 1);
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
	if (!threads || !philo->fork)
		return (0);
	if (!init_threads(philo, threads))
		return (0);
	if (!init_mutex(philo))
		return (0);
	while (++i < philo->nb_philo)
		if (pthread_create(&threads[i].thread, NULL,
				simulation_fct, &threads[i]) != 0)
			return (0);
	stop_threads(threads);
	i = -1;
	while (++i < philo->nb_philo)
		if (pthread_join(threads[i].thread, NULL) != 0)
			return (0);
	return (1);
}
