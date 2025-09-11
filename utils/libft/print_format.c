/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:35:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/19 17:27:01 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += print_pointer_address((long)(va_arg(ap, void *)), 16);
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit((long)(va_arg(ap, int)), 10);
	else if (specifier == 'u')
		count += print_digit((long)(va_arg(ap, unsigned int)), 10);
	else if (specifier == 'x')
		count += print_digit((long)(va_arg(ap, unsigned int)), 16);
	else if (specifier == 'X')
		count += print_digit_upperhexa((long)(va_arg(ap, unsigned int)), 16);
	else
		count += write(1, &specifier, 1);
	return (count);
}
