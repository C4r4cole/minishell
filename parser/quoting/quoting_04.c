/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:34:32 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:30:25 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_open_bracket(char c)
{
	return (c == OPEN_BRACKET);
}

int	is_hash(char c)
{
	return (c == HASH);
}

int	is_tilde(char c)
{
	return (c == TILDE);
}

int	is_equal(char c)
{
	return (c == EQUAL);
}

int	is_percent(char c)
{
	return (c == PERCENT);
}