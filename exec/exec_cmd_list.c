/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/18 20:35:24 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	handle_shell_altering_builtins(t_cmd *cmd, t_shell *shell)
{
	if (cmd->redir)
		return (-2);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, shell));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, shell));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, shell));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd->argv, shell));
	return (-1);
}

void	echo_pwd_env_behavior(char *cmd_name, t_cmd *cmd, t_shell *shell)
{
	int	ret;

	if (!ft_strcmp(cmd_name, "echo"))
	{
		ret = ft_echo(cmd->argv);
		child_cleanup_and_exit(shell, ret);
	}
	if (!ft_strcmp(cmd_name, "pwd"))
	{
		ret = ft_pwd(shell);
		child_cleanup_and_exit(shell, ret);
	}
	if (!ft_strcmp(cmd_name, "env"))
	{
		ret = ft_env(shell);
		child_cleanup_and_exit(shell, ret);
	}
}

static int	run_in_child_process(t_cmd *current, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		sig;

	pid = fork();
	if (pid == 0)
		execute_command_in_child(current, shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "^C\n", 3);
		else if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		shell->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

int	execute_cmds_list(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	int		exit_code;

	if (cmds->next)
		return (execute_piped_cmds(cmds, shell));
	if (heredoc_before_fork(cmds, shell) == -1)
		return (shell->exit_status = 130, 130);
	current = cmds;
	while (current)
	{
		if (!current->argv || !current->argv[0])
		{
			exit_code = apply_redirs_noop_files(current->redir);
			apply_redirs_noop_heredocs(current->redir);
			close_heredoc_fds_parent(current);
		}
		else
			exit_code = handle_shell_altering_builtins(current, shell);
		if (exit_code != -1 && exit_code != -2)
			shell->exit_status = exit_code;
		else
			run_in_child_process(current, shell);
		current = current->next;
	}
	return (shell->exit_status);
}
