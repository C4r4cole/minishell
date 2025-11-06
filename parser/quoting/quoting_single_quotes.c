/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_single_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 14:07:42 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_single_quote(char c)
{
	return (c == SINGLE_QUOTE);
}

int	set_in_single(t_splitter *initialized, char *input)
{
	if (is_single_quote(input[initialized->i]))
	{
		initialized->in_single = 1;
		initialized->i++;
		return (1);
	}
	return (0);
}

int	unset_in_single(t_splitter *initialized, char *input)
{
	if (is_single_quote(input[initialized->i]))
	{
		initialized->in_single = 0;
		initialized->i++;
		return (1);
	}
	return (0);
}
