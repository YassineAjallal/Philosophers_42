/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:02:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/02/24 18:39:18 by yajallal         ###   ########.fr       */
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

typedef struct s_details {
	pthread_t thread;
	int id;
	int status;
	pthread_mutex_t *fork;
	int	nb_philo;
} t_details;

typedef struct s_philo {
	t_details *philos;
	pthread_mutex_t *fork;
	int	nb_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int nb_times;
} t_philo;


int	ft_atoi(char *str);
int	ft_isdigit(int c);

void init_philo(t_philo *philo, char **av);
int check_arg(t_philo *philo);

int create_thread(t_philo *philo);


#endif