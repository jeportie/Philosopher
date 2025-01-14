/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:19:43 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:45:32 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_print_parsing(t_simu *simu)
{
	int	i;

	printf("Printing Params...\n\n");
	printf("num_philo       : %d\n", simu->rdonly.num_philo);
	printf("time_to_die     : %dms\n", simu->rdonly.time_to_die);
	printf("time_to_eat     : %dms\n", simu->rdonly.time_to_eat);
	printf("time_to_sleep   : %dms\n", simu->rdonly.time_to_sleep);
	printf("(optional)num_meals : %d\n", simu->rdonly.num_meals);
	printf("\n");
	i = 0;
	while (i < simu->rdonly.num_philo)
	{
		printf("Philo %d:\n", i + 1);
		printf("   pid: [not yet set or is %d]\n", simu->philos[i].pid);
		i++;
	}
	printf("\n");
}

void	ft_print_start_stop(t_simu *simu, bool is_start)
{
	long long	now;

	now = ft_get_time_ms() - simu->rdonly.start_time;
	if (is_start)
		printf(GREEN "[0ms] Simulation Starts.\n" RESET);
	else
	{
		printf(GREEN "[%lldms] Simulation Ended.\n\n" RESET, now);
	}
}

static void	ft_print_action(t_philo *ph, long long elapsed, const char *msg)
{
	printf("%lld %d %s\n", elapsed, ph->id, msg);
}

void	ft_print_state(t_philo *ph, int state)
{
	long long	elapsed;

	sem_wait(ph->simu->sem_print);
	elapsed = ft_get_time_ms() - ph->rdonly->start_time;
	if (state == DEAD)
	{
		printf(RED "%lld %d died\n" RESET, elapsed, ph->id);
		return ;
	}
	else if (state == THINK)
		ft_print_action(ph, elapsed, "is thinking");
	else if (state == LEFT || state == RIGHT)
		ft_print_action(ph, elapsed, "has taken a fork");
	else if (state == EAT)
		ft_print_action(ph, elapsed, "is eating");
	else if (state == SLEEP)
		ft_print_action(ph, elapsed, "is sleeping");
	else if (state == STOP)
		ft_print_action(ph, elapsed, "stop");
	sem_post(ph->simu->sem_print);
}
