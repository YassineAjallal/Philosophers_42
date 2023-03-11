/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 17:43:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *func_thread(void *p)
{
	t_details *thread = (t_details *)p;
	while(1)
	{
		if(!mutex_lock(thread))
			break;
		if (thread->nb_eat == thread->philo->nb_times)
		{
			thread->is_finish = 1;
			break;
		}
		printf("%lld %d is sleeping\n", get_time() - thread->philo->time_start ,thread->id + 1);
		own_sleep(thread->philo->time_sleep);
		printf("%lld %d is thinking\n", get_time() - thread->philo->time_start, thread->id + 1);
	}
	return (NULL);
}
int create_thread(t_philo *philo)
{
	t_details *threads;
	// int *is_died;
	int i;
	i = 0;
	threads = malloc(sizeof(t_details) * philo->nb_philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!threads)
		return (0);
	if (!philo->fork)
		return (0);
	while (i < philo->nb_philo)
	{
		threads[i].id = i;
		threads[i].last_eat_time = get_time();
		threads[i].nb_eat = 0;
		threads[i].philo = philo;
		threads[i].is_died = 0;
		threads[i].is_finish = 0;
		
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
		i = 0;	
		while (i < philo->nb_philo)
		{	
			if(pthread_create(&threads[i].thread, NULL, func_thread, &threads[i]) != 0)
				return (0);
			i++;
		}
		i = 0;
		while (i < philo->nb_philo)
		{
			if (threads[i].is_died == 1)
			{
				printf("%lld %d is died\n", get_time() - threads[i].philo->time_start ,threads[i].id + 1);
				return (0);	
			}
			// else if (threads[i].is_finish == 1)
			// 	return (0);
			i++;
			if (i == philo->nb_philo)
				i = 0;
		}
		i = 0;
		while (i < philo->nb_philo)
		{	
			if (pthread_join(threads[i].thread, NULL) != 0)
				return (0);
			i++;
		}
	return (1);
}


// number_of_philosophers: the number of threads my program should be running.

// time_to_die: the time where a thread shouldn't exceed in thinking (waiting for resources).

// time_to_eat: The time where a thread is locking both mutexes (eating phase).

// time_to_sleep: The time where a thread will go to sleep after eating (sleeping).

// number_of_times_each_philosopher_must_eat: The limit of times a philosopher can eat.

// You have to display a small log where each philosopher is doing an action in the following format: (timestamp) (PHILO_ID) (doing an action)