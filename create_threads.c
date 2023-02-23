/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/02/20 18:46:47 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *print(void *p)
{
	int i = *(int *)p;
	printf("thread: %d\n", i + 1);
	return (NULL);
}

int create_thread(t_philo *philo)
{
	int i;
	
	i = 0;
	philo->philo = malloc(sizeof(pthread_t) * philo->nb_philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->philo || !philo->fork)
		return (0);
	while (i < philo->nb_philo)
	{
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		if(pthread_create(&philo->philo[i], NULL, print, &i) != 0)
			return (0);
		if (pthread_join(philo->philo[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}