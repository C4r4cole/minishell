/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:49:43 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/16 18:35:52 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

int	check_syntax_errors(char **tokens)
{
	int	i;
	
	i = 0;
	while (tokens[i])
	{
		if (is_pipe(tokens[i][0]))
		{
			if (i == 0 || !tokens[i + 1] || is_pipe(tokens[i + 1][0]))
				return (syntax_error("|"));
		}
		else if (is_redirection(tokens[i]))
		{
			if (!tokens[i + 1] || is_pipe(tokens[i + 1][0]) || is_redirection(tokens[i + 1]))
				return (syntax_error(tokens[i]));
		}
		i++;
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	int	i;
	int quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (is_double_quote(input[i]) || is_single_quote(input[i]))
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		ft_putendl_fd("syntax error: unclosed quote", 2);
		return (1);
	}
	return (0);
}
