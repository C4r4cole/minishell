/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:56 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/23 14:33:24 by ilsedjal         ###   ########.fr       */
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

char	*find_path(char *args, char **envp)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	path = getenv("PATH");
	if (!path)
	{
		printf("path not found");
		return (NULL);
	}
	// je split les paths avec :
	// je teste tout les chemins avec access
	// si un chemin est ok je le retourne
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
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

int	exec_one_cmd(char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*bin;

	bin = find_path(argv[0], envp);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		execve(bin, argv, envp);
		perror("error 127");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}