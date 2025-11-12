/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:16:20 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/12 10:38:44 by ilsedjal         ###   ########.fr       */
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
	int		type;
	char	*file;
	int		was_quoted;

	was_quoted = 0;
	if (!tokens[*i + 1])
		return (0);
	type = redirection_type(tokens, i);
	file = redirection_file(tokens, i);
	if (!prepare_redirection_file(type, &file, &was_quoted))
		return (0);
	if (!finalize_and_push_redir(type, file, was_quoted, redirection_list))
		return (0);
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
		return (cleanup_build_cmd_args(redirection_list), 0);
	if (!push_cmd_with_redirs(cmd_list, cmd_args, redirection_list))
		return (0);
	*redirection_list = NULL;
	return (1);
}
