/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:18:47 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/23 17:21:11 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// print log
void	print_log(t_details *thread, char *log)
{
	pthread_mutex_lock(&thread->philo->m_is_dead);
	if (thread->philo->is_died != 1)
		printf("%lld %d %s\n", get_time() - thread->philo->time_start,
			thread->id + 1, log);
	pthread_mutex_unlock(&thread->philo->m_is_dead);
}

// libft functions
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	res;

	i = 0;
	signe = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * signe);
}

// time functions
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
