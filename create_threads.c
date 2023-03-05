/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/05 14:11:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *print(void *p)
{
	t_details *thread = (t_details *)p;
	while(1)
	{
		
		if (thread->nb_eat == thread->philo->nb_times)
		{
			// printf("---> Philo Id : %d {{     die    }}\n", thread->id + 1);
			thread->status = 1;
			break;
		}
		pthread_mutex_lock(&thread->philo->fork[thread->id]);
		pthread_mutex_lock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
		printf("%lld %d has taken a fork\n", current_time() - thread->philo->time_start ,thread->id + 1);
		printf("%lld %d is eating\n", current_time() - thread->philo->time_start ,thread->id + 1);
		usleep(thread->philo->time_eat);
		thread->nb_eat++;
		pthread_mutex_unlock(&thread->philo->fork[thread->id]);
		pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1) % thread->philo->nb_philo]);
		printf("%lld %d is sleeping\n", current_time() - thread->philo->time_start ,thread->id + 1);
		usleep(thread->philo->time_sleep);
		printf("%lld %d is thinking\n", current_time() - thread->philo->time_start, thread->id + 1);
	}
	return (NULL);
}
int create_thread(t_philo *philo)
{
	t_details *threads;
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
		threads[i].status = 0;
		threads[i].nb_eat = 0;
		threads[i].philo = philo;
		
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
		i = 0;	
		while (i < philo->nb_philo)
		{	
			if(pthread_create(&threads[i].thread, NULL, print, &threads[i]) != 0)
				return (0);
			i++;
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