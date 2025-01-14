/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:00:17 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:44:01 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

bool	ft_launch_processes(t_simu *simu)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_perror("Error: fork failed\n");
			return (false);
		}
		else if (pid == 0)
		{
			ft_routine(&simu->philos[i]);
			exit(0);
		}
		else
			simu->philos[i].pid = pid;
		i++;
	}
	return (true);
}

void	ft_wait_for_processes(t_simu *simu)
{
	int		status;
	int		count_finished;
	pid_t	ended;
	int		code;

	count_finished = 0;
	while (1)
	{
		ended = waitpid(-1, &status, 0);
		if (ended == -1)
			return ;
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
			if (code == 0)
			{
				count_finished++;
				if (count_finished == simu->rdonly.num_philo)
					break ;
			}
			else
				break ;
		}
	}
}

void	ft_kill_all(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		if (simu->philos[i].pid > 0)
			kill(simu->philos[i].pid, SIGKILL);
		i++;
	}
}
