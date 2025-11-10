/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:16:20 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 21:11:34 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
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
			skip_quotes(str, &i, &j, res);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (free(str), res);
}

int	handle_redirection(char **tokens, int *i, t_redir **redirection_list)
{
	t_redir	*new_redir;
	int		type;
	char	*file;
	char	*tmp;
	int		was_quoted;

	if (!tokens[*i + 1])
		return (0);
	type = redirection_type(tokens, i);
	file = redirection_file(tokens, i);
	if (type == HEREDOC && file[0] == '\1')
	{
		was_quoted = 1;
		tmp = ft_strdup(file + 1);
		free(file);
		file = tmp;
	}
	// was_quoted = str_has_quote(file);
	tmp = remove_quotes(file);
	if (!tmp)
		return (free(file), 0);
	file = tmp;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (free(file), 0);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	if (type == HEREDOC && !was_quoted)
		new_redir->expand_heredoc = 1;
	else
		new_redir->expand_heredoc = 0;
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

int	handle_command(char **tokens, int *i, t_cmd **cmd_list,
		t_redir **redirection_list)
{
	char	**cmd_args;
	t_cmd	*cmd;
	int		start;
	int		count;

	start = *i;
	while (tokens[*i] && tokens[*i][0] && !is_pipe(tokens[*i][0])
		&& !is_redirection(tokens[*i]))
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
