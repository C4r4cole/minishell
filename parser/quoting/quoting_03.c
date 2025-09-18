/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:26:50 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/17 17:13:32 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int is_backtick(char c)
{
	return (c == '`');
}

int	is_space(char c)
{
	return (c == ' ');
}

int is_tab(char c)
{
	return (c == '\t');
}

int	is_new_line(char c)
{
	return (c == '\n');
}

int	is_star(char c)
{
	return (c == '*');
}
