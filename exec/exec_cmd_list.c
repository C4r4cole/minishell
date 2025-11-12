/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/12 14:01:20 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static int	apply_redirs_noop(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIRECTION_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
				return (perror(redir->file), 1);
			close(fd);
		}
		else if (redir->type == REDIRECTION_OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			close(fd);
		}
		else if (redir->type == REDIRECTION_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->file), 1);
			close(fd);
		}
		else if (redir->type == HEREDOC)
		{
			if (redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	handle_shell_altering_builtins(t_cmd *cmd, t_shell *shell)
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

static void	execute_command_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;
	char	*path;

	cmd_name = cmd->argv[0];
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->redir)
		execute_redirections_cmds(cmd);
	if (!ft_strcmp(cmd_name, "echo"))
		exit(ft_echo(cmd->argv));
	if (!ft_strcmp(cmd_name, "pwd"))
		exit(ft_pwd(shell));
	if (!ft_strcmp(cmd_name, "env"))
		exit(ft_env(shell));
	if (!ft_strcmp(cmd_name, "cd") || !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset") || !ft_strcmp(cmd_name, "exit"))
		exit(handle_shell_altering_builtins(cmd, shell));
	path = find_path(cmd, shell);
	if (!path)
		exit(shell->exit_status);
	execve(path, cmd->argv, shell->envp);
	perror("execve");
	free(path);
	exit(126);
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
			exit_code = apply_redirs_noop(current->redir);
			/* ensure any heredoc FDs not consumed are closed */
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
