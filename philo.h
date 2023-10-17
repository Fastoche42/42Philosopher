/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:34:10 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/04 15:34:36 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_var
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}					t_var;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_var			*var;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*disp;
	unsigned long	last_meal;
}					t_philo;

int				ft_atoi(char *str);
int				exit_error(void);
int				check_arg(char **v);
int				arg_to_param(t_var *var, char **v);
void			assign_param(t_philo *philo, t_var *var,
					pthread_mutex_t *m, pthread_mutex_t *pr);
int				free_param(t_philo *philo, pthread_mutex_t *m,
					t_var *var);
int				init_param(t_philo *philo, t_var *var);
void			destroy_mutex(t_philo *philo);
unsigned long	in_time(void);
unsigned long	real_time(t_philo *philo);
void			display(t_philo *philo, unsigned long time, char *is_doing);
void			*thrd_loop(void *p);
void			func(t_philo *philo, t_var *var);

#endif
