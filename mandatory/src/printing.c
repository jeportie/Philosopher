/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:36:12 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/16 09:16:40 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_print_format(t_philo *philo, long long time, const char *format)
{
	pthread_mutex_lock(&philo->mtdata->stop_mutex);
	if (philo->mtdata->stop_flag == true)
	{
		pthread_mutex_unlock(&philo->mtdata->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->mtdata->stop_mutex);
	pthread_mutex_lock(&philo->mtdata->print_mutex.pmutex);
	if (DEBUG == true)
		printf("[%lldms] %d %s\n", time, philo->id, format);
	else
		printf("%lld %d %s\n", time, philo->id, format);
	pthread_mutex_unlock(&philo->mtdata->print_mutex.pmutex);
}

void	ft_print_state(t_philo *philo, int state)
{
	long long	time;

	time = ft_get_time_ms() - philo->rdonly->start_time;
	if (state == DEAD)
	{
		pthread_mutex_lock(&philo->mtdata->print_mutex.pmutex);
		if (DEBUG == true)
			printf(RED "[%lldms] %d died\n" RESET, time, philo->id);
		else
			printf(RED "%lld %d died\n" RESET, time, philo->id);
		philo->mtdata->print_mutex.is_locked = true;
		return ;
	}
	if (state == THINK)
		ft_print_format(philo, time, "is thinking");
	if (state == LEFT || state == RIGHT)
		ft_print_format(philo, time, "has taken a fork");
	if (state == EAT)
		ft_print_format(philo, time, "is eating");
	if (state == SLEEP)
		ft_print_format(philo, time, "is sleeping");
	if (state == STOP)
		ft_print_format(philo, time, RED "thread stop" RESET);
}

void	ft_print_start_stop(t_simu *simu, bool choice)
{
	if (choice == true)
		printf(GREEN "[0ms] Simulation Starts.\n" RESET);
	else
	{
		printf(GREEN "[%lldms] Simulation Ended.\n\n" RESET,
			ft_get_time_ms() - simu->rdonly.start_time);
	}
}

void	ft_print_parsing(t_simu simu)
{
	int	i;

	printf("Printing Params...\n\n");
	printf("num_philo : %d\n", simu.rdonly.num_philo);
	printf("time_to_die : %dms\n", simu.rdonly.time_to_die);
	printf("time_to_eat : %dms\n", simu.rdonly.time_to_eat);
	printf("time_to_sleep : %dms\n", simu.rdonly.time_to_sleep);
	printf("(optional)num_meals : %d\n", simu.rdonly.num_meals);
	printf("\n");
	i = 0;
	while (i < simu.rdonly.num_philo)
	{
		printf("\nPhilo %d:\n\n", i);
		printf("id : %d\n", i + 1);
		printf("thread id: %lu\n", (unsigned long)simu.philos[i].thread);
		printf("r fork : %p, l fork : %p)\n",
			simu.philos[i].right_fork, simu.philos[i].left_fork);
		i++;
	}
}
