/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_05.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:47:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/16 15:49:09 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_percent(char c)
{
	return (c == PERCENT);
}

int is_o_curly_bracket(char c)
{
	return (c == O_CURLY_BRACKET);
}

int is_c_curly_bracket(char c)
{
	return (c == C_CURLY_BRACKET);
}
