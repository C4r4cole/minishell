/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 16:29:41 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	not_quoted_actions(t_splitter *initialized, char *input, t_shell *shell)
{
	if (add_split_meta_len(initialized, input))
		return (1);
	if (add_split_on_space(initialized, input))
		return (1);
	if (set_in_single(initialized, input))
		return (1);
	if (set_in_double(initialized, input))
		return (1);
	if (expand_and_join(initialized, input, shell))
		return (1);
	return (0);
}

int	double_quote_actions(t_splitter *initialized, char *input, t_shell *shell)
{
	if (unset_in_double(initialized, input))
		return (1);
	if (expand_and_join(initialized, input, shell))
		return (1);
	return (0);
}

int	actions_on_quotes(t_splitter *initialized, char *input, t_shell *shell)
{
	if (!initialized->in_single && !initialized->in_double)
	{
		if (not_quoted_actions(initialized, input, shell))
			return (1);
	}
	else if (initialized->in_single)
	{
		if (unset_in_single(initialized, input))
			return (1);
	}
	else if (initialized->in_double)
	{
		if(double_quote_actions(initialized, input, shell))
			return (1);
	}
	return (0);
}

char **input_splitter(char *input, t_shell *shell)
{
	t_splitter	*initialized;
	char		**result;

	initialized = splitter_init();
    while (input[initialized->i])
	{
		if(actions_on_quotes(initialized, input, shell))
			continue ;
        initialized->buf = str_append_char(initialized->buf, input[initialized->i]);
        initialized->i++;
    }
    if (initialized->buf[0] != '\0')
        initialized->output = add_split(initialized->output, &initialized->count, initialized->buf, ft_strlen(initialized->buf));
    result = initialized->output;
	free_splitter(initialized);
    return (result);
}
