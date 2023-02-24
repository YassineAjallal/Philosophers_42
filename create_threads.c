/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:57:55 by yajallal          #+#    #+#             */
/*   Updated: 2023/02/24 18:51:10 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// void *take_fork(t_philo *philo)
// {
// 		int i;
// 		i = -1;		
// 		i++;	
// 		// pthread_mutex_unlock(&philo->fork[i]);
// 		// pthread_mutex_unlock(&philo->fork[(i + 1) % 9]);
// 		// philo->philos[i].status = 1;
// 	return (NULL);
// }
void *print(void *p)
{
	t_details *philo = (t_details *)p;
	while(1)
	{	
		pthread_mutex_lock(&philo->fork[philo->id]);
		pthread_mutex_lock(&philo->fork[(philo->id + 1) % philo->nb_philo]);
		printf("---> Philo Id : %d taken fork\n", philo->id + 1);
		printf("---> Philo Id : %d Eating\n", philo->id + 1);
		sleep(10);
		pthread_mutex_unlock(&philo->fork[philo->id]);
		pthread_mutex_unlock(&philo->fork[(philo->id + 1) % philo->nb_philo]);
		printf("---> Philo Id : %d thinking\n", philo->id + 1);
	}
	// if (pthread_mutex_trylock(&philo->fork[i]) == 0)
	// else
	// 	printf("fork number : %d is locked\n", i);

	// i = 0;
	// while(i < philo->nb_philo)
	// {
	// 	if (philo->philos[i].status == 1)
	// 		printf("Philo Id : %d taken fork\n", philo->philos[i].id);
	// 	i++;
	// }
	return (NULL);
}
int create_thread(t_philo *philo)
{
	int i;
	
	i = 0;
	philo->philos = malloc(sizeof(t_details) * philo->nb_philo);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	if (!philo->philos)
		return (0);
	while (i < philo->nb_philo)
	{
		philo->philos[i].id = i;
		philo->philos[i].status = 0;
		philo->philos[i].fork = philo->fork;
		philo->philos[i].nb_philo = philo->nb_philo;
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	i = 0;
	// while(1)
	// {	
		while (i < philo->nb_philo)
		{	
			if(pthread_create(&philo->philos[i].thread, NULL, print, &philo->philos[i]) != 0)
				return (0);
			i++;
		}
		i = 0;
		while (i < philo->nb_philo)
		{	
			if (pthread_join(philo->philos[i].thread, NULL) != 0)
				return (0);
			i++;
		}
	// }
	return (1);
}