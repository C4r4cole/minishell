/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:01 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/17 17:40:37 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_quoting_symbols(char c)
{
	return (is_pipe(c) || is_slash(c) || is_hyphen(c) || is_underscore(c)
			|| is_dollar(c) || is_question_mark(c) || is_double_quote(c)
			|| is_single_quote(c) || is_redirection_in(c) || is_redirection_out(c)
			|| is_open_bracket(c) || is_tilde(c) || is_percent(c) || is_ampersand(c)
			|| is_semicolon(c) || is_opening_parenthesis(c) || is_closing_parenthesis(c)
			|| is_backtick(c) || is_space(c) || is_tab(c) || is_new_line(c) || is_backslash(c)
			|| is_star(c) || is_hash(c) || is_equal(c));
}
