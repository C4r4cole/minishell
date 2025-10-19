/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:16:20 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/19 15:24:07 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int is_redirection(char *present_token)
{
	if (!present_token)
		return (0);
	return (ft_strcmp(present_token, "<") == 0
			|| ft_strcmp(present_token, ">") == 0
			|| ft_strcmp(present_token, "<<") == 0
			|| ft_strcmp(present_token, ">>") == 0);
}

int	handle_redirection(char **tokens, int *i, t_redir **redirection_list)
{
	t_redir	*new_redir;
	
    if (tokens[*i + 1])
    {
		new_redir = ft_redirnew(tokens[*i], tokens[*i + 1]);
        ft_rediradd_back(redirection_list, new_redir);
        *i += 2;
        return (1);
    }
    return (0);
}

char	**create_cmd_args(char **tokens, int start, int count)
{
	char	**before_pipe_tokens_tab;
    int		j;
	
    before_pipe_tokens_tab = malloc(sizeof(char *) * (count + 1));
    if (!before_pipe_tokens_tab)
		return (NULL);
    j = 0;
    while (j < count)
    {
		before_pipe_tokens_tab[j] = ft_strdup(tokens[start + j]);
        if (!before_pipe_tokens_tab[j])
        {
			while (j > 0)
			free(before_pipe_tokens_tab[--j]);
            free(before_pipe_tokens_tab);
            return (NULL);
        }
        j++;
    }
    before_pipe_tokens_tab[j] = NULL;
    return (before_pipe_tokens_tab);
}

int	handle_command(char **tokens, int *i, t_cmd **cmd_list, t_redir **redirection_list)
{
	char	**cmd_args;
    t_cmd	*cmd;
    int		start;
    int		count;
	
    start = *i;
    while (tokens[*i] && tokens[*i][0] && !is_pipe(tokens[*i][0]) && !is_redirection(tokens[*i]))
	(*i)++;
    count = *i - start;
    if (count <= 0)
		return (1);
    cmd_args = create_cmd_args(tokens, start, count);
    if (!cmd_args)
		return (0);
    cmd = ft_cmdnew(cmd_args, *redirection_list);
    ft_cmdadd_back(cmd_list, cmd);
    *redirection_list = NULL;
    return (1);
}

int	handle_pipe(int *i)
{
	(*i)++;
	return (1);
}
