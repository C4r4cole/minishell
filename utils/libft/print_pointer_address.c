/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer_address.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:35:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/19 19:08:56 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer_address(long n, int base)
{
	int		count;

	if (!n)
		return (write(1, "(nil)", 5));
	count = print_str("0x");
	count += print_digit_pointer(n, base);
	return (count);
}
