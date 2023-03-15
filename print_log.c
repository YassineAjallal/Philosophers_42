/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:36:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/15 13:01:33 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_log(t_details *thread, char *log)
{
	if (!death_checker(thread))
		return (0);
	printf("%lld %d %s\n",
			get_time() - thread->philo->time_start, thread->id + 1, log);
	return (1);
}