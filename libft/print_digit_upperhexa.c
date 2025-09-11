/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit_upperhexa.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:35:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/19 18:00:18 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit_upperhexa(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		print_char('-');
		return (print_digit_upperhexa(-n, base) + 1);
	}
	else if (n < base)
		return (print_char(symbols[n]));
	else
	{
		count = print_digit_upperhexa(n / base, base);
		return (count + print_digit_upperhexa(n % base, base));
	}
}
