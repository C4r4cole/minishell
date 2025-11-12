/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:50:21 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/12 13:45:30 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static void	handle_heredoc_cmd(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
		perror("dup2");
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
}

static void	handle_redir_in_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

static void	handle_redir_out_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

static void	handle_redir_append_cmd(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

void	execute_redirections_cmds(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			handle_heredoc_cmd(redir);
		else if (redir->type == REDIRECTION_IN)
			handle_redir_in_cmd(redir);
		else if (redir->type == REDIRECTION_OUT)
			handle_redir_out_cmd(redir);
		else if (redir->type == REDIRECTION_APPEND)
			handle_redir_append_cmd(redir);
		redir = redir->next;
	}
}
