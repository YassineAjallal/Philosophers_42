/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/23 21:56:10 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// handle the one philo case
int	one_philo(t_details *thread)
{
	if (thread->philo->nb_philo == 1)
	{
		pthread_mutex_lock(&thread->philo->fork[thread->id]);
		print_log(thread, "has taken a fork");
		own_sleep(thread->philo->time_die);
		pthread_mutex_lock(&thread->philo->m_is_dead);
		thread->philo->is_died = 1;
		pthread_mutex_unlock(&thread->philo->m_is_dead);
		pthread_mutex_unlock(&thread->philo->fork[thread->id]);
		return (0);
	}
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

void	*simulation_fct(void *p)
{
	t_details	*thread;

	thread = (t_details *)p;
	if ((thread->id + 1) % 2 == 0)
		usleep(1000);
	if (!one_philo(thread))
		return (0);
	while (1)
	{
		if (!death_checker(thread))
			return (NULL);
		if (!mutex_lock(thread))
			return (NULL);
		if (!eat_checker(thread))
			return (NULL);
		print_log(thread, "is sleeping");
		own_sleep(thread->philo->time_sleep);
		print_log(thread, "is thinking");
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
	{
		free(threads);
		return (0);
	}
	while (++i < philo->nb_philo)
		if (pthread_create(&threads[i].thread, NULL,
				simulation_fct, &threads[i]) != 0)
		{
			free(threads);
			return (0);
		}
	stop_threads(threads);
	i = -1;
	while (++i < philo->nb_philo)
	{
		if (pthread_join(threads[i].thread, NULL) != 0)
		{
			free(threads);
			return (0);
		}
	}
	free(threads);
	return (1);
}
