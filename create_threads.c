/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/02/23 12:50:54 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void take_fork(t_philo *philo)
{
	int i;
	i = 0;
	while (i < philo->nb_philo)
	{
		if (i == 0)
		{
			if (philo->philos[philo->nb_philo - 1].status == 0 && philo->philos[i + 1].status == 0)
			{	
				pthread_mutex_lock(&philo->fork[i]);
				pthread_mutex_lock(&philo->fork[philo->nb_philo - 1]);
				philo->philos[i].status = 1;
			}
		}
		else if (i == philo->nb_philo - 1)
		{
			if (philo->philos[i - 1].status == 0 && philo->philos[0].status == 0)
			{	
				pthread_mutex_lock(&philo->fork[0]);
				pthread_mutex_lock(&philo->fork[i]);
				philo->philos[i].status = 1;
			}
		}
		else
		{
			if (philo->philos[i - 1].status == 0 && philo->philos[i + 1].status == 0)
			{	
				pthread_mutex_lock(&philo->fork[i]);
				pthread_mutex_lock(&philo->fork[i + 1]);
				philo->philos[i].status = 1;
			}
		}
		i++;
	}
}
void *print(void *p)
{
	t_philo *philo = (t_philo *)p;
	int i;
	i = 0;
	take_fork(philo);
	while(i < philo->nb_philo)
	{
		if (philo->philos[i].status == 1)
			printf("Philo Id : %d taken fork\n", philo->philos[i].id);
		i++;
	}
	return (NULL);
}
int create_thread(t_philo *philo)
{
	int i;
	
	i = 0;
	philo->philos = malloc(sizeof(t_details) * philo->nb_philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->philos || !philo->fork)
		return (0);
	while (i < philo->nb_philo)
	{
		philo->philos[i].id = i;
		philo->philos[i].status = 0;
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		if(pthread_create(&philo->philos[i].thread, NULL, print, philo) != 0)
			return (0);
		if (pthread_join(philo->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}