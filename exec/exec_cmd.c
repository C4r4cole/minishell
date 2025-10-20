/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/20 17:43:12 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	execute_cmds_list(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	current = cmds;
	tmp = cmds;
	while (tmp)
	{
		if (heredoc_before_fork(tmp))
			return (1);
		tmp = tmp->next;
	}
	while (current)
	{
		if (ft_strcmp(current->argv[0], "echo") == 0
		|| ft_strcmp(current->argv[0], "pwd") == 0
		|| ft_strcmp(current->argv[0], "env") == 0)
		{
			if (current->redir)
			{
				pid = fork();
				status = 0;
				if (pid == 0)
				{
					if (execute_redirections_builtins(current->redir))
						exit(1);
					if (ft_strcmp(current->argv[0], "echo") == 0)
						exit(ft_echo(current->argv));
					else if (ft_strcmp(current->argv[0], "pwd") == 0)
						exit(ft_pwd(shell));
					else
						exit(ft_env(shell));
				}
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					shell->exit_status = WEXITSTATUS(status);
				else
					shell->exit_status = 1;
			}
			else
			{
				if (ft_strcmp(current->argv[0], "echo") == 0)
					shell->exit_status = ft_echo(current->argv);
				else if (ft_strcmp(current->argv[0], "pwd") == 0)
					shell->exit_status = ft_pwd(shell);
				else 
					shell->exit_status = ft_env(shell);
			}
		}
		else if (ft_strcmp(current->argv[0], "cd") == 0
			|| ft_strcmp(current->argv[0], "export") == 0
			|| ft_strcmp(current->argv[0], "exit") == 0)
		{
			if (ft_strcmp(current->argv[0], "cd") == 0)
				shell->exit_status = ft_cd(current->argv,shell);
			else if (ft_strcmp(current->argv[0], "export") == 0)
				shell->exit_status = ft_export(current->argv, shell); // ajouter le export tout seul qui met les variables dans l'ordre alphabetique
			// else if (ft_strcmp(current->argv[0], "exit") == 0)
				// handle exit
		}
		else
		{
			shell->exit_status = exec_one_cmd(current, shell->envp);
		}
		current = current->next;
	}
	return (shell->exit_status);
}
