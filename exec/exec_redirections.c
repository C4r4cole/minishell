/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:50:21 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/20 17:03:21 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void execute_redirections_cmds(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		fd;
	char	*path;
	char 	**envp;

	envp = env_to_tab(env);
	path = find_path(cmd, envp);
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
            if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
            {
                perror("dup2");
				exit (1);
            }
			close(redir->heredoc_fd);
		}
		else if (redir->type == REDIRECTION_IN)
		{
			fd = open(redir->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIRECTION_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIRECTION_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	execve(path, cmd->argv, envp);
	perror("execve");
	free_tab(envp);
	exit(EXIT_FAILURE);
}

int execute_redirections_builtins(t_redir *redir)
{
	int		fd;
	
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
            if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
                return (perror("dup2 heredoc"), 1);
			close(redir->heredoc_fd);
		}
		else if (redir->type == REDIRECTION_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
				return (perror(redir->file), 1);
			if (dup2(fd, STDIN_FILENO) < 0)
				return (perror("dup2 in"), close(fd), 1);
			close(fd);
		}
		else if (redir->type == REDIRECTION_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (perror("dup2 out"), close(fd), 1);
			close(fd);
		}
		else if (redir->type == REDIRECTION_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (perror("dup2 append"), close(fd), 1);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
