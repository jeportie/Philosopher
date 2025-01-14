/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:06:30 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/13 14:54:30 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_safe_thread_init(t_simu *simu)
{
	if (!ft_init_threads(simu))
	{
		ft_stop_threads(simu);
		ft_free_philos(simu);
		ft_perror("Thread init failed.\n");
		return (false);
	}
	return (true);
}

void	ft_links_init(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		simu->philos[i].left_fork = &simu->forks[i];
		simu->philos[i].right_fork = &simu->forks[(i + 1)
			% simu->rdonly.num_philo];
		simu->forks[i].left_philo = &simu->philos[i];
		simu->forks[i].right_philo = &simu->philos[(i + 1)
			% simu->rdonly.num_philo];
		i++;
	}
}

bool	ft_safe_simulation_init(t_simu *simu, int ac, char **av)
{
	if (!ft_init_mtdata(simu) || !ft_init_rdonly(simu, ac, av))
		return (false);
	if (!ft_init_philos(simu) || !ft_init_forks(simu))
	{
		ft_free_philos(simu);
		return (false);
	}
	ft_links_init(simu);
	ft_init_monitor(simu);
	if (!ft_safe_thread_init(simu))
		return (false);
	return (true);
}
