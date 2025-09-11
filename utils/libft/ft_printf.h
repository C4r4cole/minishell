/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:36:23 by fmoulin           #+#    #+#             */
/*   Updated: 2025/06/25 16:25:17 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	print_format(char specifier, va_list ap);
int	print_str(char *str);
int	print_char(int c);
int	print_digit(long n, int base);
int	print_digit_upperhexa(long n, int base);
int	print_digit_pointer(unsigned long n, unsigned int base);
int	print_pointer_address(long n, int base);

#endif