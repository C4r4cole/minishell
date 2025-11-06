/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:06:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/05 16:06:27 by ilsedjal         ###   ########.fr       */
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

	tmp = env;
	count = 0;
	i = 0;
	while (tmp && ++count)
		tmp = tmp->next;
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		tmp2 = ft_strjoin(env->key, "=");
		tab[i] = ft_strjoin(tmp2, env->value);
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

char	*handle_direct_path(char *cmd_name, t_shell *shell)
{
	struct stat	st;

	if (stat(cmd_name, &st) == 0 && S_ISDIR(st.st_mode))
	{
		shell->exit_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		return (ft_putstr_fd(": Is a directory\n", 2), NULL);
	}
	if (access(cmd_name, F_OK) != 0)
	{
		shell->exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), NULL);
	}
	if (access(cmd_name, X_OK) != 0)
	{
		shell->exit_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		return (ft_putstr_fd(": Permission denied\n", 2), NULL);
	}
	return (ft_strdup(cmd_name));
}

char	*find_path(t_cmd *cmd, t_shell *shell)
{
	char	**paths;
	char	*full_path;
	char	*path_var;
	int		i;

	i = -1;
	if (ft_strchr(cmd->argv[0], '/'))
		return (handle_direct_path(cmd->argv[0], shell));
	path_var = env_get_value(shell->envp_lst, "PATH");
	if (!path_var)
		return (shell->exit_status = 127, ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(cmd->argv[0], 2),
			ft_putstr_fd(": No such file or directory\n", 2), NULL);
	paths = ft_split(path_var, ':');
	while (paths[++i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->argv[0]);
		if (access(full_path, X_OK) == 0)
			return (free_tab(paths), full_path);
		free(full_path);
	}
	shell->exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	return (ft_putstr_fd(": command not found\n", 2), free_tab(paths), NULL);
}
