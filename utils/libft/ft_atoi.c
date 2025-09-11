/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:46:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/06 19:36:20 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	sign;
	size_t	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == 9 || nptr[i] == 10
		|| nptr[i] == 11 || nptr[i] == 12
		|| nptr[i] == 13 || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*nbr;

	nbr = "     -532";
	printf("%d\n", ft_atoi(nbr));
	printf("%d\n", atoi(nbr));
	return (0);
}
*/