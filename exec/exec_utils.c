/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:56 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/25 14:52:17 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

void	init_shell(t_shell *shell)
{
	shell->pwd = getcwd(NULL, 0); // ← INITIALISE CORRECTEMENT
	if (!shell->pwd)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	shell->oldpwd = NULL;
	shell->envp = NULL;
	shell->exit_status = 0;
}

void	free_shell(t_shell *shell)
{
	if (shell->pwd)
		free(shell->pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
}

char	*find_path(t_cmd *arg)
{
	char	*path;
	char	**paths = NULL;
	char	*tmp;
	int		i;
	char	*full_path;
	i = 0;

	path = getenv("PATH");
	if (!path)
	{
		printf("path not found");
		return (NULL);
	}
	// je split les paths avec :
	// je teste tout les chemins avec access
	// si un chemin est ok je le retourne
	paths = ft_split(path,':');
	while (paths[i])
	{
		
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp,arg->argv[0]);
		// free le join
		if (access(tmp, X_OK) == 0)
		{
			return (tmp);
		}
		i++;
		free(tmp);
	}
	return (NULL);
}

int	exec_one_cmd(t_cmd *arg, char **envp)
{
	pid_t	pid;
	int		status;
	char	*bin;

	bin = find_path(arg);
	pid = fork();
	if (pid < 0)
	{
		free(bin);
		return (1);
	}
	if (pid == 0)
	{
		execve(bin, arg->argv, envp);
		perror("error 127");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}