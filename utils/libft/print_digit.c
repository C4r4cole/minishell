/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:35:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/19 19:13:38 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		print_char('-');
		return (print_digit(-n, base) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n]));
	else
	{
		count = print_digit(n / base, base);
		return (count + print_digit(n % base, base));
	}
}

int	print_digit_pointer(unsigned long n, unsigned int base)
{
	unsigned int		count;
	char				*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		if (n <= -base)
		{
			count = print_digit(n / (-base), base);
			count += print_digit((n % base) * (-1), base);
			return (count);
		}
		return (print_digit(-n, base));
	}
	else if (n >= base)
	{
		count = print_digit(n / base, base);
		count += print_digit(n % base, base);
		return (count);
	}
	else
	{
		return (print_char(symbols[n]));
	}
}
