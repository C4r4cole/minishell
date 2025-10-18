/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/18 19:07:57 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_empty_input(char *user_input)
{
	int	i;

	i = 0;
	if (!user_input)
		return (1);
	while (user_input[i] && user_input[i] == ' ')
		i++;
	return (!user_input[i]);
}

char	**get_tokens(char *user_input, t_env *env)
{
	char	**tokens;
	char	**split;

	split = input_splitter(user_input);
	if (!split)
		return (NULL);
	tokens = quotes_management(split, env);
	if (!tokens || !tokens[0])
	{
		if (tokens)
			free(tokens);
		return (NULL);
	}
	return (tokens);
}

void	cleanup_parse_error(t_cmd *cmd_list, t_redir *redirection_list, char **tokens)
{
	free_cmd_list(cmd_list);
	free_redir_list(redirection_list);
	free_tokens(tokens);
}

t_cmd	*parse_input(char *user_input, t_env *env)
{
	char	**tokens;
    t_cmd	*cmd_list;
    t_redir	*redirection_list;
    int		i;

	if (is_empty_input(user_input))
		return (NULL);
    tokens = get_tokens(user_input, env);
	if (!tokens)
        return (NULL);
	if (check_syntax_errors(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
    cmd_list = NULL;
    redirection_list = NULL;
    i = 0;
    while (tokens[i])
    {
        while (tokens[i] && is_redirection(tokens[i]))
        {
            if (!handle_redirection(tokens, &i, &redirection_list))
                break;
        }
        if (tokens[i] && tokens[i][0] && !is_pipe(tokens[i][0]))
        {
            if (!handle_command(tokens, &i, &cmd_list, &redirection_list))
                return (cleanup_parse_error(cmd_list, redirection_list, tokens), NULL);
        }
		else if (tokens[i] && is_pipe(tokens[i][0]))
		{
			if (!handle_pipe(&i))
				break;
		}
        else
            i++;
    }
	if (redirection_list)
		free_redir_list(redirection_list);
	free_tokens(tokens);
    return (cmd_list);
}
