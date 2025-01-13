/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:26:10 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/12 21:50:40 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_free_remaining_forks(int i, t_simu *simu)
{
	while (i--)
		pthread_mutex_destroy(&simu->forks[i].fork_mutex);
	free(simu->forks);
}

bool	ft_init_forks(t_simu *simu)
{
	int		i;
	t_forks	*forks;

	forks = (t_forks *)malloc(sizeof(t_forks) * simu->rdonly.num_philo);
	if (!forks)
	{
		ft_perror("Memory Allocation failed to create t_philo *philos.\n");
		return (false);
	}
	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		memset(&forks[i], 0, sizeof(t_forks));
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0
			|| pthread_mutex_init(&forks[i].lock_mutex, NULL) != 0
			|| pthread_mutex_init(&forks[i].request_mutex, NULL) != 0)
		{
			ft_perror("Mutex init failed.\n");
			ft_free_remaining_forks(i, simu);
			return (false);
		}
		i++;
	}
	simu->forks = forks;
	return (true);
}

static void	ft_join_remaining_threads(int i, t_simu *simu)
{
	while (i)
	{
		pthread_join(simu->philos[i].thread, NULL);
		i--;
	}
}

bool	ft_init_threads(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, ft_routine,
				&simu->philos[i]) != 0)
		{
			ft_perror("Thread creation failed.\n");
			ft_join_remaining_threads(i, simu);
			return (false);
		}
		i++;
	}
	if (pthread_create(&simu->monitor.thread, NULL, ft_monitor, &simu->monitor)
		!= 0)
	{
		ft_perror("Thread creation failed.\n");
		ft_join_remaining_threads(i, simu);
		pthread_join(simu->monitor.thread, NULL);
		return (false);
	}
	return (true);
}
