/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:35:00 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/18 18:51:03 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static void	execve_or_exit(t_cmd *cmds, t_shell *shell)
{
	char	*path;
	char	**env_tab;

	path = find_path(cmds, shell);
	if (!path)
		child_cleanup_and_exit(shell, shell->exit_status);
	env_tab = env_to_tab(shell->envp_lst);
	if (!env_tab)
		free_path_env_tab(path, shell);
	execve(path, cmds->argv, env_tab);
	perror("execve");
	free_tab(env_tab);
	free(path);
	child_cleanup_and_exit(shell, 126);
}

void	execute_child_command(t_cmd *cmds, t_shell *shell)
{
	int		handled;
	int		code;

	if (!cmds->argv || !cmds->argv[0])
		child_cleanup_and_exit(shell, 0);
	code = try_child_builtin(cmds->argv, shell, &handled);
	if (handled)
		child_cleanup_and_exit(shell, code);
	execve_or_exit(cmds, shell);
}

void	child_io_setup(t_cmd *cmds, int in_fd, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
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

void	parent_io_management(t_cmd *cmds, int *in_fd, pid_t pid, int *fd)
{
	(void)pid;
	if (*in_fd != -1)
		close(*in_fd);
	if (cmds->next)
	{
		close(fd[1]);
		*in_fd = fd[0];
	}
	free_redir_list(cmds->redir);
	cmds->redir = 0;
}

pid_t	spawn_stage(t_cmd *current, int in_fd, int fd[2], t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		child_io_setup(current, in_fd, fd);
		execute_child_command(current, shell);
	}
	return (pid);
}
