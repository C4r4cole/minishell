/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:37:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 21:25:25 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static char *heredoc_expand_line(char *str, t_shell *shell)
{
	int	i;
	char *out;
	char *exp;
	char *tmp;
	char buf[2];

	i = 0;
	out = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			exp = expand_one_dollar(str, &i, shell);
			tmp = ft_strjoin(out, exp);
			free(out);
			free(exp);
			out = tmp;
		}
		else
		{
			buf[0] = str[i];
			buf[1] = 0;
			tmp = ft_strjoin(out, buf);
			free(out);
			out = tmp;
			i++;
		}
	}
	return (out);
}

static void	heredoc_child_routine(int *fd, char *end_word, int expand, t_shell *shell)
{
	char	*line;
	char	*to_write;
	char	*expanded;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, handle_sigquit);
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
		to_write = line;
		if (expand)
		{
			expanded = heredoc_expand_line(line, shell);
			free(line);
			to_write = expanded;
		}
		write(fd[1], to_write, ft_strlen(to_write));
		write(fd[1], "\n", 1);
		free(to_write);
	}
	close(fd[1]);
	_exit(0);
}

int	handle_heredoc(char *end_word, int expand, t_shell *shell)
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
		heredoc_child_routine(fd, end_word, expand, shell);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGQUIT, handle_sigquit);
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

int	heredoc_before_fork(t_cmd *cmd, t_shell *shell)
{
	t_redir	*r;
	int		fd;

	r = cmd->redir;
	while (r)
	{
		if (r->type == HEREDOC)
		{
			fd = handle_heredoc(r->file, r->expand_heredoc, shell);
			if (fd == -1)
				return (-1);
			r->heredoc_fd = fd;
		}
		r = r->next;
	}
	return (0);
}

int	heredoc_before_fork_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (heredoc_before_fork(current, shell) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
