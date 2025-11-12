/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_builtins.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:03:34 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 13:45:33 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static int	handle_heredoc_builtin(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
		return (perror("dup2 heredoc"), 1);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}

static int	handle_redir_in_builtin(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (perror(redir->file), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2 in"), close(fd), 1);
	close(fd);
	return (0);
}

static int	handle_redir_out_builtin(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2 out"), close(fd), 1);
	close(fd);
	return (0);
}

static int	handle_redir_append_builtin(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2 append"), close(fd), 1);
	close(fd);
	return (0);
}

int	execute_redirections_builtins(t_redir *redir)
{
	int	ret;

	while (redir)
	{
		ret = 0;
		if (redir->type == HEREDOC)
			ret = handle_heredoc_builtin(redir);
		else if (redir->type == REDIRECTION_IN)
			ret = handle_redir_in_builtin(redir);
		else if (redir->type == REDIRECTION_OUT)
			ret = handle_redir_out_builtin(redir);
		else if (redir->type == REDIRECTION_APPEND)
			ret = handle_redir_append_builtin(redir);
		if (ret != 0)
			return (ret);
		redir = redir->next;
	}
	return (0);
}
