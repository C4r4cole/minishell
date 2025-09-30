/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:49:56 by ilsedjal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/25 15:11:48 by ilsedjal         ###   ########.fr       */
=======
/*   Updated: 2025/09/29 15:31:57 by fmoulin          ###   ########.fr       */
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
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

<<<<<<< HEAD
char	*find_path(t_cmd *arg)
=======
char	*find_path(char *cmd)
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
{
	char	*path;
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;
<<<<<<< HEAD
	char	*full_path;
	i = 0;
=======
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736

	path = getenv("PATH");
	if (!path)
		return (NULL);
<<<<<<< HEAD
	}
	// je split les paths avec :
	// je teste tout les chemins avec access
	// si un chemin est ok je le retourne
	paths = ft_split(path,':');
=======
	paths = ft_split(path, ':'); // ← remplir correctement paths
	if (!paths)
		return (NULL);

	i = 0;
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
	while (paths[i])
	{
		
		tmp = ft_strjoin(paths[i], "/");
<<<<<<< HEAD
		full_path = ft_strjoin(tmp,arg->argv[0]);
		// free le join
		if (access(tmp, X_OK) == 0)
		{
			return (tmp);
		}
		i++;
=======
		full_path = ft_strjoin(tmp, cmd); // concatène avec la commande
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
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

<<<<<<< HEAD
int	exec_one_cmd(t_cmd *arg, char **envp)
=======

int	exec_one_cmd(char **argv, char **envp)
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
{
	pid_t	pid;
	int		status;
	char	*bin;

<<<<<<< HEAD
	bin = find_path(arg);
=======
	bin = find_path(argv[0]);
	if (!bin)
	{
		ft_printf("%s: command not found\n", argv[0]);
		return (127);
	}
>>>>>>> f85283a89606eecda4a9efe4056ab5890c0e1736
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