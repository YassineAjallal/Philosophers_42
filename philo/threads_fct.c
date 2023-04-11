/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:35:40 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/09 22:48:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philo *philo, t_details *threads)
{
	int			i;
	long long	start_eat_time;

	i = 0;
	start_eat_time = get_time();
	while (i < philo->nb_philo)
	{
		threads[i].id = i;
		threads[i].last_eat_time = start_eat_time;
		threads[i].nb_eat = 0;
		threads[i].philo = philo;
		threads[i].philo->is_died = 0;
		threads[i].is_finish = 0;
		i++;
	}
	if (!init_mutex(philo))
		return (0);
	return (1);
}

void	*start_thread(void *p)
{
	t_details	*thread;

	thread = (t_details *)p;
	if ((thread->id + 1) % 2 == 0)
		usleep(1000);
	if (!one_philo(thread))
		return (0);
	while (1)
	{
		if (!death_checker(thread))
			return (NULL);
		if (!mutex_lock(thread))
			return (NULL);
		if (!eat_checker(thread))
			return (NULL);
		print_log(thread, "is sleeping");
		own_sleep(thread->philo->time_sleep);
		print_log(thread, "is thinking");
	}
	return (NULL);
}

int	set_dead(t_details *thread)
{
	if (get_time() - thread->last_eat_time >= thread->philo->time_die)
	{
		pthread_mutex_lock(&thread->philo->m_is_dead);
		printf("%lld %d died\n", get_time() - thread->philo->time_start,
			thread->id + 1);
		thread->philo->is_died = 1;
		pthread_mutex_unlock(&thread->philo->m_is_dead);
		return (0);
	}
	return (1);
}

int	stop_threads(t_details *threads)
{
	int	i;

	i = 0;
	while (i < threads[0].philo->nb_philo)
	{
		pthread_mutex_lock(&threads[i].philo->m_eat);
		if (!set_dead(&threads[i]))
		{
			pthread_mutex_unlock(&threads[i].philo->m_eat);
			return (0);
		}
		else if (check_nb_eat(threads))
		{
			pthread_mutex_unlock(&threads[i].philo->m_eat);
			return (0);
		}
		pthread_mutex_unlock(&threads[i].philo->m_eat);
		i++;
		if (i == threads[0].philo->nb_philo)
			i = 0;
	}
	return (1);
}
