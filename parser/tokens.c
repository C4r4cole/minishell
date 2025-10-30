/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:16:20 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/30 11:44:58 by fmoulin          ###   ########.fr       */
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

int	get_redir_type(char *token)
{
	if (!ft_strcmp(token, "<"))
		return (REDIRECTION_IN);
	if (!ft_strcmp(token, ">"))
		return (REDIRECTION_OUT);
	if (!ft_strcmp(token, ">>"))
		return (REDIRECTION_APPEND);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	return (-1);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

int	handle_redirection(char **tokens, int *i, t_redir **redirection_list)
{
	t_redir	*new_redir;
	int		type;

	if (!tokens[*i + 1])
		return (0);

	type = get_redir_type(tokens[*i]);
	if (type == -1)
		return (0);

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);

	new_redir->type = type;
	new_redir->file = remove_quotes(ft_strdup(tokens[*i + 1]));
	new_redir->next = NULL;

	ft_rediradd_back(redirection_list, new_redir);
	*i += 2;
	return (1);
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
