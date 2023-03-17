/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:58:20 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/17 19:40:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	own_sleep(int time_to_sleep)
{
	long long	curr;

	curr = get_time();
	while (1)
	{
		usleep(100);
		if (get_time() - curr == time_to_sleep)
			break ;
	}
}
