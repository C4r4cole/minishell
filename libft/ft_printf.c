/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:35:57 by fmoulin           #+#    #+#             */
/*   Updated: 2025/07/15 15:16:31 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (-1);
	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	int		count;
// 	char	*str;

// 	str = NULL;
// 	count = ft_printf("%p\n", &str);
// 	ft_printf("The chars written are %d\n", count);
// 	count = printf("%p\n", &str);
// 	printf("The chars written are %d\n", count);
// }
