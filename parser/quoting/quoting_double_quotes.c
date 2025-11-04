/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_double_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 16:24:16 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_double_quote(char c)
{
	return (c == DOUBLE_QUOTE);
}

int	set_in_double(t_splitter *initialized, char *input)
{
	if (is_double_quote(input[initialized->i]))
	{
		initialized->in_double = 1;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	unset_in_double(t_splitter *initialized, char *input)
{
	if (is_double_quote(input[initialized->i]))
	{
		initialized->in_double = 0;
		initialized->i++;
		return (1);
	}
	return (0);
}