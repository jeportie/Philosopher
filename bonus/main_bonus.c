/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:50:00 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:33:07 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

int	main(int ac, char **av)
{
	t_simu	simu;

	memset(&simu, 0, sizeof(t_simu));
	if (!ft_init_bonus(&simu, ac, av))
		return (1);
	if (!ft_launch_processes(&simu))
	{
		ft_kill_all(&simu);
		return (1);
	}
	ft_wait_for_processes(&simu);
	ft_kill_all(&simu);
	sem_close(simu.sem_forks);
	sem_close(simu.sem_print);
	if (simu.sem_death)
		sem_close(simu.sem_death);
	sem_unlink("sem_forks");
	sem_unlink("sem_print");
	sem_unlink("sem_death");
	free(simu.philos);
	return (0);
}
