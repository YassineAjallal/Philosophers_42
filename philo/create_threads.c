/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/09 22:45:52 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(t_details *threads, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&threads[i].thread, NULL,
				start_thread, &threads[i]) != 0)
		{
			free(threads);
			return (0);
		}
		i++;
	}
	return (1);
}

int	thread_detach(t_details *threads, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_detach(threads[i].thread) != 0)
		{
			free(threads);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_thread(t_philo *philo)
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
	if (!thread_create(threads, philo))
		return (0);
	stop_threads(threads);
	if (!thread_detach(threads, philo))
		return (0);
	free(threads);
	return (1);
}
