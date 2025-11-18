/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/18 20:39:39 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static void	handle_child_redirs_or_exit(t_cmd *cmd, t_shell *shell)
{
	if (cmd->redir && execute_redirections_cmds(cmd) != 0)
	{
		free_cmd_list(shell->current_cmd_list);
		free_shell(shell);
		exit(1);
	}
}

static void	handle_child_builtin_or_exit(t_cmd *cmd, t_shell *shell)
{
	int	code;

	if (!ft_strcmp(cmd->argv[0], "cd") || !ft_strcmp(cmd->argv[0], "export")
		|| !ft_strcmp(cmd->argv[0], "unset") || !ft_strcmp(cmd->argv[0],
			"exit"))
	{
		code = handle_shell_altering_builtins(cmd, shell);
		child_cleanup_and_exit(shell, code);
	}
}

void	execute_command_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;
	char	*path;
	char	**env_tab;

	cmd_name = cmd->argv[0];
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_child_redirs_or_exit(cmd, shell);
	echo_pwd_env_behavior(cmd_name, cmd, shell);
	handle_child_builtin_or_exit(cmd, shell);
	path = find_path(cmd, shell);
	if (!path)
		child_cleanup_and_exit(shell, shell->exit_status);
	env_tab = env_to_tab(shell->envp_lst);
	if (!env_tab)
		free_path_env_tab(path, shell);
	execve(path, cmd->argv, env_tab);
	child_cleanup_and_exit_execve(shell, 126, path, env_tab);
}
