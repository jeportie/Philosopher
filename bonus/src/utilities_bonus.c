/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:28:50 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/14 21:06:28 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long long	ft_get_time_ms(void)
{
	t_timeval	tv;
	long long	time;
	int			succes;

	succes = gettimeofday(&tv, NULL);
	if (succes == -1)
	{
		ft_perror("Error, time not found.\n");
		return (-1);
	}
	time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
	return (time);
}

static long long	ft_get_elapsed_time_us(t_timeval start, t_timeval end)
{
	long long	sec;
	long long	usec;

	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	return (sec * 1000000L + usec);
}

void	ft_precise_usleep(long long usec)
{
	t_timeval	start;
	t_timeval	current;
	long long	elapsed;
	long long	rem;

	gettimeofday(&start, NULL);
	elapsed = 0;
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = ft_get_elapsed_time_us(start, current);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else if (rem > 0)
			usleep(rem);
	}
}

void	ft_perror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}
