/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:52:27 by jeportie          #+#    #+#             */
/*   Updated: 2024/08/19 11:36:43 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ft_is_int_help(char *nptr, int i, int sign, int len)
{
	if (len == 10)
	{
		if (sign == -1)
		{
			if (ft_strncmp(&nptr[i], "2147483648", 10) > 0)
				return (false);
		}
		else
		{
			if (ft_strncmp(&nptr[i], "2147483647", 10) > 0)
				return (false);
		}
	}
	if (len > 10)
		return (false);
	return (true);
}

bool	ft_is_int(char *nptr)
{
	int	len;
	int	i;
	int	sign;

	len = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i], &sign))
		i++;
	while (nptr[i] == '0')
		i++;
	while (nptr[len + i])
	{
		if (!ft_isdigit(nptr[len + i]))
			return (false);
		len++;
	}
	if (len < 10)
		return (true);
	if (!ft_is_int_help(nptr, i, sign, len))
		return (false);
	return (true);
}

bool	ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_is_int(av[i]))
			return (false);
		i++;
	}
	return (true);
}
