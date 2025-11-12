/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:39:57 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 14:42:37 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	apply_redirs_noop_files(t_redir *redir)
{
	int	fd;
	int	flags;

	while (redir)
	{
		flags = 0;
		if (redir->type == REDIRECTION_IN)
			flags = O_RDONLY;
		else if (redir->type == REDIRECTION_OUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (redir->type == REDIRECTION_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			redir = redir->next;
			continue ;
		}
		fd = open(redir->file, flags, 0644);
		if (fd < 0)
			return (perror(redir->file), 1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

void	apply_redirs_noop_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == HEREDOC && redir->heredoc_fd != -1)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}
