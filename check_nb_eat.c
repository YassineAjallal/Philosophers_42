/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:20:33 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/11 18:32:35 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_nb_eat(t_details *threads, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (threads[i].is_finish != 1)
			return (0);
		i++;
	}
	return (1);
}
