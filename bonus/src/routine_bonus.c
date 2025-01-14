/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:06:41 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:41:54 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NOTE: PHILOSOPHERS THREADS */

#include "../include/philo_bonus.h"

static bool	ft_check_death(t_philo *ph)
{
	long long	now;

	now = ft_get_time_ms();
	if ((now - ph->last_meal_time) >= ph->rdonly->time_to_die)
	{
		ft_print_state(ph, DEAD);
		return (true);
	}
	return (false);
}

void	ft_routine(t_philo *ph)
{
	ph->last_meal_time = ft_get_time_ms();
	if (ph->start_offset > 0)
		ft_precise_usleep(ph->start_offset * 1000);
	if (ph->rdonly->num_philo == 1)
	{
		sem_wait(ph->simu->sem_forks);
		ft_print_state(ph, LEFT);
		ft_precise_usleep(ph->rdonly->time_to_die * 1000);
		ft_print_state(ph, DEAD);
		exit(ph->id);
	}
	while (true)
	{
		ft_print_state(ph, THINK);
		ft_eat(ph);
		if (ph->rdonly->num_meals > 0
			&& ph->meals_eaten >= ph->rdonly->num_meals)
			exit(0);
		if (ft_check_death(ph))
			exit(ph->id);
		ft_sleep_and_think(ph);
		if (ft_check_death(ph))
			exit(ph->id);
	}
}

void	ft_eat(t_philo *ph)
{
	sem_wait(ph->simu->sem_forks);
	ft_print_state(ph, LEFT);
	sem_wait(ph->simu->sem_forks);
	ft_print_state(ph, RIGHT);
	ft_print_state(ph, EAT);
	ph->last_meal_time = ft_get_time_ms();
	ph->meals_eaten++;
	ft_precise_usleep(ph->rdonly->time_to_eat * 1000);
	sem_post(ph->simu->sem_forks);
	sem_post(ph->simu->sem_forks);
}

void	ft_sleep_and_think(t_philo *ph)
{
	ft_print_state(ph, SLEEP);
	ft_precise_usleep(ph->rdonly->time_to_sleep * 1000);
}
