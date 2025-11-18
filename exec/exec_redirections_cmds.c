/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:50:21 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/18 20:14:54 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static int	handle_heredoc_cmd(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
		return (1);
	}
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}

static int	handle_redir_in_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_out_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_append_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	execute_redirections_cmds(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (handle_heredoc_cmd(redir))
				return (1);
		}
		else if (redir->type == REDIRECTION_IN)
		{
			if (handle_redir_in_cmd(redir))
				return (1);
		}
		else if (redir->type == REDIRECTION_OUT)
		{
			if (handle_redir_out_cmd(redir))
				return (1);
		}
		else if (redir->type == REDIRECTION_APPEND)
		{
			if(handle_redir_append_cmd(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
