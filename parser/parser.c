/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/02 14:46:41 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parse_input(char *user_input, t_env *env)
{
	char	**tokens;
    t_cmd	*cmd_list;
    t_redir	*redirection_list;
    int		i;

	if (!user_input)
        return (NULL);
	i = 0;
	while (user_input[i] && user_input[i] == ' ')
		i++;
	if (!user_input[i])
		return (NULL);
    tokens = quotes_management(input_splitter(user_input), env);
	if (!tokens)
        return (NULL);
	if (!tokens[0])
	{
		free(tokens);
		return (NULL);
	}
    cmd_list = NULL;
    redirection_list = NULL;
    i = 0;
    while (tokens[i])
    {
        if (is_redirection(tokens[i]))
        {
            if (!handle_redirection(tokens, &i, &redirection_list))
                break;
        }
        else if (tokens[i][0] && !is_pipe(tokens[i][0]))
        {
            if (!handle_command(tokens, &i, &cmd_list, &redirection_list))
			{
				free_cmd_list(cmd_list);
				free_redir_list(redirection_list);
				free_tokens(tokens);
                return (NULL);
			}
        }
		else if (is_pipe(tokens[i][0]))
		{
			if (!handle_pipe(&i))
				break;
		}
        else
            i++;
    }
	if (redirection_list)
		free_redir_list(redirection_list);
	free(tokens);
    return (cmd_list);
}
