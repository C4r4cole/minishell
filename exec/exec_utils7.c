/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:27:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/18 20:29:30 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static int	skip_sign(const char *str, int *sign)
{
	int	index;

	index = 0;
	*sign = 1;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			*sign = -1;
		index++;
	}
	if (!str[index])
		return (-1);
	return (index);
}

static int	check_digits(const char *str, long long *result, int sign,
		int index)
{
	int	digit;

	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (1);
		digit = str[index] - '0';
		if (sign == 1 && *result > (LLONG_MAX - digit) / 10)
			return (1);
		if (sign == -1 && (-*result < (LLONG_MIN + digit) / 10))
			return (1);
		*result = *result * 10 + digit;
		index++;
	}
	return (0);
}

int	is_ll_overflow(const char *str)
{
	long long	result;
	int			sign;
	int			index;

	result = 0;
	index = skip_sign(str, &sign);
	if (index < 0)
		return (1);
	return (check_digits(str, &result, sign, index));
}
