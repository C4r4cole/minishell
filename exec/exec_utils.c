/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:56 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/29 15:31:57 by fmoulin          ###   ########.fr       */
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

char	*find_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':'); // ← remplir correctement paths
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd); // concatène avec la commande
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			// ⚠️ libérer paths avant de return
			int j = 0;
			while (paths[j])
				free(paths[j++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// libérer paths si rien trouvé
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}


int	exec_one_cmd(char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*bin;

	bin = find_path(argv[0]);
	if (!bin)
	{
		ft_printf("%s: command not found\n", argv[0]);
		return (127);
	}
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