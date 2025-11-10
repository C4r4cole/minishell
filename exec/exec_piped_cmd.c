/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:58:33 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/10 19:54:36 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static void	execute_child_command(t_cmd *cmds, t_shell *shell)
{
	char	*path;
	int		code;

	if (!ft_strcmp(cmds->argv[0], "export") || !ft_strcmp(cmds->argv[0],
			"unset") || !ft_strcmp(cmds->argv[0], "cd"))
		exit(1);
	if (!ft_strcmp(cmds->argv[0], "exit"))
	{
		code = ft_exit_return_code(cmds->argv);
		if (!ft_isnumber(cmds->argv[1]))
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(code);
	}
	if (!ft_strcmp(cmds->argv[0], "echo"))
		exit(ft_echo(cmds->argv));
	if (!ft_strcmp(cmds->argv[0], "pwd"))
		exit(ft_pwd(shell));
	if (!ft_strcmp(cmds->argv[0], "env"))
		exit(ft_env(shell));
	path = find_path(cmds, shell);
	if (!path)
		exit(shell->exit_status);
	execve(path, cmds->argv, shell->envp);
	perror("execve");
	exit(126);
}

static void	child_io_setup(t_cmd *cmds, int in_fd, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (in_fd != -1)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			(perror("dup2 in"), exit(1));
		close(in_fd);
	}
	if (cmds->next)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			(perror("dup2 out"), exit(1));
		close(fd[1]);
	}
	if (cmds->redir)
		execute_redirections_cmds(cmds);
}

static void	wait_for_all_children(pid_t last_pid, t_shell *shell)
{
	pid_t	w;
	int		status;
	int		sig;

	while (1)
	{
		w = waitpid(-1, &status, 0);
		if (w == -1)
			break ;
		if (w == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					write(2, "Quit (core dumped)\n", 20);
				shell->exit_status = 128 + sig;
			}
		}
	}
}
// gestion pipe cote parent

static void	parent_io_management(t_cmd *cmds, int *in_fd, pid_t pid, int *fd)
{
	(void)pid;
	if (*in_fd != -1)
		close(*in_fd);
	if (cmds->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
}

int	execute_piped_cmds(t_cmd *cmds, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	int (in_fd) = -1;
	pid_t (last_pid) = -1;
	signal(SIGPIPE, SIG_IGN);
	shell->in_pipe = 1;
	if (heredoc_before_fork_all(cmds, shell) == -1)
		return (shell->exit_status = 130, 130);
	while (cmds)
	{
		if (cmds->next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			(child_io_setup(cmds, in_fd, fd), execute_child_command(cmds,
					shell));
		last_pid = pid;
		parent_io_management(cmds, &in_fd, pid, fd);
		cmds = cmds->next;
	}
	return (wait_for_all_children(last_pid, shell), shell->in_pipe = 0,
		shell->exit_status);
}
