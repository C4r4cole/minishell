/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:01 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/30 11:46:13 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_metacharacter(char c)
{
	return (is_pipe(c) || is_redirection_in(c) || is_redirection_out(c) || is_ampersand(c)
			|| is_semicolon(c) || is_opening_parenthesis(c) || is_closing_parenthesis(c)
			|| is_space(c));
}

int	is_quote(char c)
{
	return (is_double_quote(c) || is_single_quote(c));
}

int	is_litteral_value_exception(char c)
{
	return (is_dollar(c) || is_backtick(c) || is_backslash(c));
}
