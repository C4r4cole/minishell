/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:06:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/30 14:31:55 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec_header.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		count;
	int		i;
	char	*tmp2;

	count = 0;
	i = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tmp2 = ft_strjoin("=", env->value);
		tab[i] = ft_strjoin(env->key, tmp2);
		free(tmp2);
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '/';
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*find_path(t_cmd *cmd, t_shell *shell)
{
	char *cmd_name;
	char **paths;
	char *full_path;
	int i;
	struct stat st;
	char *path_var;

	cmd_name = cmd->argv[0];
	paths = NULL;
	i = -1;
	// Cas 1 : contient un '/' → commande relative ou absolue
	if (ft_strchr(cmd_name, '/'))
	{
		if (stat(cmd_name, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				shell->exit_status = 126;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd_name, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				return (NULL);
			}
		}
		if (access(cmd_name, F_OK) != 0)
		{
			shell->exit_status = 127;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (NULL);
		}
		if (access(cmd_name, X_OK) != 0)
		{
			shell->exit_status = 126;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (NULL);
		}
		return (ft_strdup(cmd_name));
	}
	// Cas 2 : sinon cherche dans PATH
	// while (shell->envp && shell->envp[++i])
	// {
	// 	if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
	// 	{
	// 		paths = ft_split(shell->envp[i] + 5, ':');
	// 		break ;
	// 	}
	// }
	// if (!paths)
	// {
	// 	shell->exit_status = 127;
	// 	return (NULL);
	// }

	path_var = env_get_value(shell->envp_lst, "PATH");
	if (!path_var)
	{
		shell->exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	paths = ft_split(path_var, ':');
	
	// Cas 3 : tester chaque dossier de PATH
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin_path(paths[i], cmd_name);
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
	}
	// Commande introuvable
	shell->exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_tab(paths);
	return (NULL);
}