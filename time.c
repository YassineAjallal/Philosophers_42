/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:58:20 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/05 14:03:56 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}
