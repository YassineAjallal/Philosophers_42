/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:02:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/05 13:27:38 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo {
	pthread_mutex_t *fork;
	int	nb_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int nb_times;
	long long last_time;
} t_philo;
typedef struct s_details {
	pthread_t thread;
	int id;
	int status;
	int nb_eat;
	t_philo *philo;
} t_details;



int	ft_atoi(char *str);
int	ft_isdigit(int c);

void init_philo(t_philo *philo, char **av);
int check_arg(t_philo *philo);

int create_thread(t_philo *philo);


#endif