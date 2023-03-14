/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:20:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/14 14:31:04 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_nb_eat(t_details *threads)
{
	int	i;
	int nb_philo;

	nb_philo = threads->philo->nb_philo;
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(&threads[i].philo->m_is_finish);
		if (threads[i].is_finish != 1)
		{
			pthread_mutex_unlock(&threads[i].philo->m_is_finish);
			return (0);
		}
		pthread_mutex_unlock(&threads[i].philo->m_is_finish);
		i++;
	}
	return (1);
}
