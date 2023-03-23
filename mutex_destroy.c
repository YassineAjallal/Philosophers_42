/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:34:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/20 14:38:36 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mutex_destroy(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->m_is_dead);
	pthread_mutex_destroy(&philo->m_is_finish);
	pthread_mutex_destroy(&philo->m_last_eat_time);
	pthread_mutex_destroy(&philo->m_nb_eat);
}