/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42ft.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:49:06 by jeportie          #+#    #+#             */
/*   Updated: 2024/08/19 09:49:42 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_issign(int c, int *sign)
{
	if (c == '+')
		return (1);
	if (c == '-')
	{
		*sign *= -1;
		return (1);
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	digit;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i], &sign))
		i++;
	while (ft_isdigit(nptr[i]))
	{
		digit = nptr[i] - '0';
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}
