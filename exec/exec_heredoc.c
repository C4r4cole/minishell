/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/05 15:57:53 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static void	heredoc_child_routine(int *fd, char *end_word)
{
	char	*line;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_printf("bash: warning: ");
			ft_printf("here-document at line 1 delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(line, end_word) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	_exit(0);
}

int	handle_heredoc(char *end_word)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
		heredoc_child_routine(fd, end_word);
	signal(SIGINT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		return (close(fd[0]), -1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		return (close(fd[0]), -1);
	}
	return (fd[0]);
}

int	heredoc_before_fork(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redir;
	while (r)
	{
		if (r->type == HEREDOC)
		{
			fd = handle_heredoc(r->file);
			if (fd == -1)
				return (-1);
			r->heredoc_fd = fd;
		}
		r = r->next;
	}
	return (0);
}

int	heredoc_before_fork_all(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (heredoc_before_fork(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
