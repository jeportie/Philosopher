/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:57:43 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:35:38 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static bool	ft_parse_and_fill_rdonly(t_simu *simu, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_perror("Wrong format!\n");
		return (false);
	}
	if (!ft_check_args(ac, av))
	{
		ft_perror("Invalid args! Only ints allowed.\n");
		return (false);
	}
	simu->rdonly.num_philo = ft_atoi(av[1]);
	simu->rdonly.time_to_die = ft_atoi(av[2]);
	simu->rdonly.time_to_eat = ft_atoi(av[3]);
	simu->rdonly.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		simu->rdonly.num_meals = ft_atoi(av[5]);
	else
		simu->rdonly.num_meals = -1;
	if (simu->rdonly.num_philo <= 0 || simu->rdonly.time_to_die < 60
		|| simu->rdonly.time_to_eat < 60 || simu->rdonly.time_to_sleep < 60)
	{
		ft_perror("Args out of range.\n");
		return (false);
	}
	return (true);
}

bool	ft_open_semaphores(t_simu *simu)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_print");
	sem_unlink("sem_death");
	simu->sem_forks = sem_open("sem_forks",
			O_CREAT | O_EXCL, 0644, simu->rdonly.num_philo);
	if (simu->sem_forks == SEM_FAILED)
		return (ft_perror("Error sem_open forks\n"), false);
	simu->sem_print = sem_open("sem_print",
			O_CREAT | O_EXCL, 0644, 1);
	if (simu->sem_print == SEM_FAILED)
		return (ft_perror("Error sem_open print\n"), false);
	simu->sem_death = sem_open("sem_death",
			O_CREAT | O_EXCL, 0644, 1);
	if (simu->sem_death == SEM_FAILED)
		return (ft_perror("Error sem_open death\n"), false);
	return (true);
}

bool	ft_init_bonus(t_simu *simu, int ac, char **av)
{
	int	i;

	if (!ft_parse_and_fill_rdonly(simu, ac, av))
		return (false);
	simu->philos = malloc(sizeof(t_philo) * simu->rdonly.num_philo);
	if (!simu->philos)
		return (ft_perror("Malloc fail for philos\n"), false);
	memset(simu->philos, 0, sizeof(t_philo) * simu->rdonly.num_philo);
	if (!ft_open_semaphores(simu))
		return (false);
	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		simu->philos[i].id = i + 1;
		simu->philos[i].pid = 0;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].rdonly = &simu->rdonly;
		simu->philos[i].simu = simu;
		simu->philos[i].start_offset = 0;
		i++;
	}
	simu->rdonly.start_time = ft_get_time_ms();
	return (true);
}
