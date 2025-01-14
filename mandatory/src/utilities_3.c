/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:08:50 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/11 14:40:46 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mtx_increment_int(t_mtx *mutex, int *dest)
{
	pthread_mutex_lock(mutex);
	*dest += 1;
	pthread_mutex_unlock(mutex);
}

void	mtx_set_llong(t_mtx *mutex, long long *dest, long long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
