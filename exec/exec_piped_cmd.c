/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:58:33 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 14:16:42 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static pid_t	run_pipeline(t_cmd *cmds, t_cmd *last, int is_shell_builtin,
		t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;
	pid_t	last_pid;
	t_cmd	*current;

	in_fd = -1;
	last_pid = -1;
	current = cmds;
	while (current)
	{
		if (is_shell_builtin && current == last)
			break ;
		if (current->next && pipe(fd) == -1)
			return (-1);
		pid = spawn_stage(current, in_fd, fd, shell);
		if (pid == -1)
			return (-1);
		last_pid = pid;
		parent_io_management(current, &in_fd, pid, fd);
		current = current->next;
	}
	return (last_pid);
}

int	execute_piped_cmds(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*last;
	int		is_shell_builtin;
	pid_t	last_pid;
	int		ret;

	find_last_and_builtin(cmds, &last, &is_shell_builtin);
	signal(SIGPIPE, SIG_IGN);
	shell->in_pipe = 1;
	if (heredoc_before_fork_all(cmds, shell) == -1)
		return (shell->in_pipe = 0, shell->exit_status = 130, 130);
	last_pid = run_pipeline(cmds, last, is_shell_builtin, shell);
	if (last_pid == -1)
		return (shell->in_pipe = 0, perror("pipe/fork"), 1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_for_all_children(last_pid, shell);
	shell->in_pipe = 0;
	if (is_shell_builtin)
	{
		ret = exec_last_builtin_parent(last, shell);
		close_heredoc_fds_parent(cmds);
		shell->exit_status = ret;
		return (ret);
	}
	return (close_heredoc_fds_parent(cmds), shell->exit_status);
}
