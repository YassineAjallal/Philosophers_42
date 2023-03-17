/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/17 19:39:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation_fct(void *p)
{
	t_details	*thread;

	thread = (t_details *)p;
	if ((thread->id) % 2 == 0)
		usleep(1500);
	if (!one_philo(thread))
		return (0);
	while (1)
	{
		if (!death_checker(thread))
			break ;
		if (!mutex_lock(thread))
			break ;
		if (!eat_checker(thread))
			break ;
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
	{
		if (pthread_join(threads[i].thread, NULL) != 0)
			return (0);
		usleep(1000);
	}
	return (1);
}
