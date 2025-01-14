/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:48:06 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/11 12:48:57 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_perror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

void	ft_stop_threads(t_simu *simu)
{
	int	i;

	if (simu->philos)
	{
		i = 0;
		while (i < simu->rdonly.num_philo)
		{
			if (simu->philos[i].thread)
				pthread_join(simu->philos[i].thread, NULL);
			i++;
		}
	}
}

void	ft_destroy_mutex(t_simu *simu)
{
	pthread_mutex_destroy(&simu->mtdata.print_mutex.pmutex);
	pthread_mutex_destroy(&simu->mtdata.stop_mutex);
	pthread_mutex_destroy(&simu->mtdata.meal_mutex);
	pthread_mutex_destroy(&simu->mtdata.go_mutex);
	pthread_mutex_destroy(&simu->mtdata.end_mutex);
	pthread_mutex_destroy(&simu->mtdata.start_mutex);
}

void	ft_free_forks(t_simu *simu)
{
	int	i;

	if (simu->forks)
	{
		i = 0;
		while (i < simu->rdonly.num_philo)
		{
			pthread_mutex_destroy(&simu->forks[i].fork_mutex);
			pthread_mutex_destroy(&simu->forks[i].lock_mutex);
			i++;
		}
		free(simu->forks);
		simu->forks = NULL;
	}
}

void	ft_free_philos(t_simu *simu)
{
	int	i;

	ft_free_forks(simu);
	if (simu->philos)
	{
		i = 0;
		while (i < simu->rdonly.num_philo)
		{
			pthread_mutex_destroy(&simu->philos[i].time_mutex);
			pthread_mutex_destroy(&simu->philos[i].finish_mutex);
			i++;
		}
		free(simu->philos);
		simu->philos = NULL;
	}
	ft_destroy_mutex(simu);
}
