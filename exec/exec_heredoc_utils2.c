/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:17:15 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 14:20:38 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

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
	t_cmd	*c;
	t_redir	*r;

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
