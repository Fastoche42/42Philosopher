/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:33:44 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/04 15:33:57 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->disp);
	printf("%lu	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->disp);
}

void	*thrd_loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_meal = in_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		display(philo, real_time(philo), "has taken a fork");
		pthread_mutex_lock(&philo->mutex[philo->id % philo->var->num_philo]);
		display(philo, real_time(philo), "has taken a fork");
		display(philo, real_time(philo), "is eating");
		philo->ate++;
		if (philo->ate == philo->var->must_eat)
			philo->var->total_ate++;
		usleep(philo->var->time_eat * 1000);
		philo->last_meal = in_time();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->var->num_philo]);
		display(philo, real_time(philo), "is sleeping");
		usleep(philo->var->time_sleep * 1000);
		display(philo, real_time(philo), "is thinking");
	}
	return (0);
}

void	func(t_philo *philo, t_var *var)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].var->total_ate == philo[i].var->num_philo)
		{
			destroy_mutex(philo);
			free_param(philo, philo->mutex, var);
			break ;
		}
		if (in_time() - philo[i].last_meal > (unsigned long)var->time_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->disp);
			printf("%lu	%d died", real_time(philo), philo->id);
			destroy_mutex(philo);
			free_param(philo, philo->mutex, var);
			break ;
		}
		i = (i + 1) % var->num_philo;
		usleep(500);
	}
}

int	exit_error(void)
{
	printf("Usage: number_of_philo time_to_die time_to_eat time_to_sleep \
 [number_of_eats]\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int			i;
	t_var		*var;
	t_philo		*philo;
	pthread_t	*th;

	if (argc < 5 || argc > 6)
		return (exit_error());
	var = (t_var *)malloc(sizeof(t_var));
	if (arg_to_param(var, argv))
		return (free_param(0, 0, var));
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_philo);
	if (init_param(philo, var))
		return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * var->num_philo);
	i = -1;
	while (++i < philo->var->num_philo)
	{
		pthread_create(&th[i], NULL, thrd_loop, philo + i);
		usleep(100);
	}
	func(philo, var);
	free(th);
	return (0);
}
