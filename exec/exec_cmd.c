/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/22 14:03:14 by ilsedjal         ###   ########.fr       */
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
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
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
			|| ft_strcmp(current->argv[0], "unset") == 0
			|| ft_strcmp(current->argv[0], "exit") == 0)
		{
			if (ft_strcmp(current->argv[0], "cd") == 0)
				shell->exit_status = ft_cd(current->argv, shell);
			else if (ft_strcmp(current->argv[0], "export") == 0)
				shell->exit_status = ft_export(current->argv, shell);
					// ajouter le export tout seul qui met les variables dans l'ordre alphabetique
			else if (ft_strcmp(current->argv[0], "unset") == 0)
				shell->exit_status = ft_unset(current->argv, shell);
			else if (ft_strcmp(current->argv[0], "exit") == 0)
				shell->exit_status = ft_exit(current->argv, shell);
		}
		else
		{
			shell->exit_status = exec_one_cmd(current, shell->envp);
		}
		current = current->next;
	}
	return (shell->exit_status);
}
int execute_piped_cmds(t_cmd *cmds, t_shell *shell)
{
    int fd[2];
    int in_fd = 0;
    pid_t pid;
    t_cmd *current = cmds;

    while (current)
    {
        if (current->next)
            pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            // Remet le handler SIGINT/SIGQUIT par défaut uniquement dans l'enfant
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (current->next)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            if (current->redir)
                execute_redirections_builtins(current->redir);
            execve(find_path(current, shell->envp), current->argv, shell->envp);
            perror("execve");
            exit(1);
        }
        // Ne touche pas aux signaux dans le parent ici !
        if (in_fd != 0)
            close(in_fd);
        if (current->next)
        {
            close(fd[1]);
            in_fd = fd[0];
        }
        current = current->next;
    }
    while (wait(NULL) > 0);
    return 0;
}
