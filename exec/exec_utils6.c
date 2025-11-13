/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:27:42 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/13 14:08:03 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

static char	*make_env_kv(t_env *env)
{
	char	*tmp;
	char	*res;

	if (env->value)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (NULL);
		res = ft_strjoin(tmp, env->value);
		free(tmp);
		return (res);
	}
	return (ft_strjoin(env->key, "="));
}

char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		count;
	int		i;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = make_env_kv(env);
		if (!tab[i])
			return (tab[i] = NULL, free_tab(tab), NULL);
		i++;
		env = env->next;
	}
	return (tab[i] = NULL, tab);
}

void	child_cleanup_and_exit(t_shell *shell, int status)
{
	if (shell && shell->current_cmd_list)
		free_cmd_list(shell->current_cmd_list);
	if (shell)
		free_shell(shell);
	exit(status);
}

void	free_path_env_tab(char *path)
{
	perror("env_to_tab");
	free(path);
	exit(126);
}
