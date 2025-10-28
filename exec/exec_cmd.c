/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:27:10 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/28 15:04:08 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

int	execute_cmds_list(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*tmp;
	pid_t	pid;
	int		status;

	if (cmds->next) // s'il y a un pipe -> on délègue à execute_piped_cmds
		return (execute_piped_cmds(cmds, shell));
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
			shell->exit_status = exec_one_cmd(current, shell);
		}
		current = current->next;
	}
	return (shell->exit_status);
}
int execute_piped_cmds(t_cmd *cmds, t_shell *shell)
{
    int fd[2];
    int in_fd = -1;
    pid_t pid;
    int status;
    int last_status = 0;

    shell->in_pipe = 1; // flag pour export & unset

    while (cmds)
    {
        if (cmds->next && pipe(fd) == -1)
            return (perror("pipe"), 1);

        pid = fork();
        if (pid == -1)
            return (perror("fork"), 1);

        if (pid == 0) // CHILD
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);

            if (in_fd != -1)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (cmds->next)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }

            if (cmds->redir)
                execute_redirections_cmds(cmds);

            // Builtins dans pipeline → exécutés localement
            if (!ft_strcmp(cmds->argv[0], "echo"))
                exit(ft_echo(cmds->argv));
            if (!ft_strcmp(cmds->argv[0], "pwd"))
                exit(ft_pwd(shell));
            if (!ft_strcmp(cmds->argv[0], "env"))
                exit(ft_env(shell));
            if (!ft_strcmp(cmds->argv[0], "export"))
                exit(1); // bash: export dans pipe → pas d'effet
            if (!ft_strcmp(cmds->argv[0], "unset"))
                exit(1);
            if (!ft_strcmp(cmds->argv[0], "cd"))
                exit(1);
            if (!ft_strcmp(cmds->argv[0], "exit"))
                exit(1);

            // Sinon commande externe
            char *path = find_path(cmds, shell->envp);
            if (!path)
                exit(127);
            execve(path, cmds->argv, shell->envp);
            perror("execve");
            exit(126);
        }

        // parent
        if (in_fd != -1)
            close(in_fd);
        if (cmds->next)
        {
            close(fd[1]);
            in_fd = fd[0];
        }

        cmds = cmds->next;
    }

    // ✅ récupérer seulement la dernière valeur de retour
    while (wait(&status) > 0)
        last_status = status;

    if (WIFEXITED(last_status))
        shell->exit_status = WEXITSTATUS(last_status);
    else if (WIFSIGNALED(last_status))
        shell->exit_status = 128 + WTERMSIG(last_status);

    shell->in_pipe = 0;
    return shell->exit_status;
}

