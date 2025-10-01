/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:01 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/01 16:09:18 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_metacharacter(char c)
{
	return (is_pipe(c) || is_redirection_in(c) || is_redirection_out(c) || is_ampersand(c)
			|| is_semicolon(c) || is_opening_parenthesis(c) || is_closing_parenthesis(c)
			|| is_space(c) || is_double_quote(c) || is_single_quote(c));
}

int	is_litteral_value_exception(char c)
{
	return (is_dollar(c) || is_backtick(c) || is_backslash(c));
}

// || is_slash(c) || is_hyphen(c) || is_underscore(c) 
// || is_question_mark(c) || is_double_quote(c) || is_single_quote(c) 
// || is_open_bracket(c) || is_tilde(c) || is_percent(c) ||
// || is_tab(c) || is_new_line(c) || is_star(c) || is_hash(c) || is_equal(c)