/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/09/30 14:05:39 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec_header.h"

int	check_n(const char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	else if (str[i] == '-')
	{
		i++;
	}
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
		{
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int	newline_flag;
	int	i;

	newline_flag = 1;
	i = 1;
	if (!argv[1])
		return (ft_printf("\n"), 0);
	while (argv[i] && check_n(argv[i]) == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline_flag)
		ft_printf("\n");
	return (0);
}

int	ft_pwd(t_shell *shell)
{
	char	*current_pwd;

	if (shell && shell->pwd)
	{
		printf("%s\n", shell->pwd);
		return (0);
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd)
	{
		ft_printf("%s\n", current_pwd);
		free(current_pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}

int	ft_cd(char **argv)
{
	char	*target;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
		target = getenv("HOME");
	else if (ft_strncmp(argv[1], "-", ft_strlen(argv[1])) == 0)
		target = oldpwd;
	else
		target = argv[1];
	if (!target)
	{
		perror("cd: no target found");
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd:");
		free(oldpwd);
		return (1);
	}
	return (0);
	// mtn il faut update les pwd dans mon **ENV ;
}

void env_update_or_add(t_env **lst, char *key, char *value)
{
	t_env *tmp = *lst;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(lst, ft_envnew(ft_strdup(key), ft_strdup(value)));
}

int	ft_env(t_shell *shell)
{
    t_env *tmp = shell->envp_lst;
    while (tmp)
    {
        if (tmp->value) // n'affiche que les variables avec une valeur
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    return (0);
}

int	ft_export(char **argv, t_shell *shell)
{
	int		i;
	char	*equal;
	int		key_len;
	char	*key;
	char	*value;

	i = 1;
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (equal)
		{
			key_len = equal - argv[i];
			key = ft_substr(argv[i], 0, key_len);
			value = ft_strdup(equal + 1);
			if (key && key[0] != '\0') // N'ajoute que si la clé n'est pas vide
				env_update_or_add(&(shell->envp_lst), key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
