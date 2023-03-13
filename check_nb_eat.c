/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:20:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/13 17:05:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_nb_eat(t_details *threads, t_philo *philo)
{
	int	i;
	int nb_philo;

	pthread_mutex_lock(&philo->mutex_list->m_nb_philo);
	nb_philo = philo->nb_philo;
	pthread_mutex_unlock(&philo->mutex_list->m_nb_philo);
	i = 0;
	while (i < nb_philo)
	{
		if (threads[i].is_finish != 1)
			return (0);
		i++;
	}
	return (1);
}
