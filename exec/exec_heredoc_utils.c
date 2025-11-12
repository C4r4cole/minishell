/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:05:00 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 13:54:37 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

char	*heredoc_expand_line(char *str, t_shell *shell)
{
	int		i;
	char	*out;

	i = 0;
	out = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			process_dollar(&out, str, &i, shell);
		}
		else
		{
			append_char_to_out(&out, str[i]);
			i++;
		}
	}
	return (out);
}

void	append_char_to_out(char **out, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = 0;
	tmp = ft_strjoin(*out, buf);
	free(*out);
	*out = tmp;
}

void	process_dollar(char **out, char *str, int *i, t_shell *shell)
{
	char	*exp;
	char	*tmp;

	exp = expand_one_dollar(str, i, shell);
	tmp = ft_strjoin(*out, exp);
	free(*out);
	free(exp);
	*out = tmp;
}

int	line_is_end(char *line, char *end_word)
{
	int	is_end;

	is_end = (ft_strcmp(line, end_word) == 0);
	if (is_end)
		free(line);
	return (is_end);
}

void	write_heredoc(int fd, char *line, int expand, t_shell *shell)
{
	char	*to_write;
	char	*expanded;

	to_write = line;
	if (expand)
	{
		expanded = heredoc_expand_line(line, shell);
		free(line);
		to_write = expanded;
	}
	write(fd, to_write, ft_strlen(to_write));
	write(fd, "\n", 1);
	free(to_write);
}

void	close_heredoc_fds_parent(t_cmd *cmds)
{
	t_cmd   *c;
	t_redir *r;

	c = cmds;
	while (c)
	{
		r = c->redir;
		while (r)
		{
			if (r->type == HEREDOC && r->heredoc_fd != -1)
			{
				close(r->heredoc_fd);
				r->heredoc_fd = -1;
			}
			r = r->next;
		}
		c = c->next;
	}
}
