/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:41:24 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/21 13:14:30 by ilsedjal         ###   ########.fr       */
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
void	update_pwd(t_shell *shell, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return ;
	}
	env_update_or_add(&(shell->envp_lst), "OLDPWD", oldpwd);
	env_update_or_add(&(shell->envp_lst), "PWD", newpwd);
	free(newpwd);
}
int	ft_cd(char **argv, t_shell *shell)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!argv[1])
		target = getenv("HOME");
	else if (ft_strncmp(argv[1], "-", ft_strlen(argv[1])) == 0)
		target = shell->oldpwd;
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
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		// free ancien shell->oldpwd
		free(shell->oldpwd);
		shell->oldpwd = oldpwd;
		free(shell->pwd);
		shell->pwd = newpwd;
		// mettre à jour dans l'env
		env_update_or_add(&(shell->envp_lst), "OLDPWD", shell->oldpwd);
		env_update_or_add(&(shell->envp_lst), "PWD", shell->pwd);
	}
	else
		free(oldpwd); // on libère si jamais getcwd a échoué
	return (0);
}

void	env_update_or_add(t_env **lst, char *key, char *value)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(lst, ft_envnew(ft_strdup(key), ft_strdup(value)));
}

int	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->envp_lst;
	while (tmp)
	{
		if (tmp->value) // n'affiche que les variables avec une valeur
			ft_printf("%s=%s\n", tmp->key, tmp->value);
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
void	env_remove(t_env **lst, char *key)
{
	t_env *prev = NULL;
	t_env *tmp = *lst;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int is_valid_env_name(const char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    if (!ft_isalpha(str[0]) && str[0] != '_') // Le premier caractère doit être une lettre ou un underscore
        return (0);
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_') // Les caractères suivants doivent être alphanumériques ou des underscores
            return (0);
        i++;
    }
    return (1);
}
int ft_unset(char **argv, t_shell *shell)
{
    int i;

    if (!argv[1])
        return (0);
    i = 1;
    while (argv[i])
    {
        if (argv[i][0] && is_valid_env_name(argv[i]))
        {
            env_remove(&(shell->envp_lst), argv[i]);
        }
        else
        {
            ft_putstr_fd("': not a valid identifier\n", 2);
            shell->exit_status = 1;
        }
        i++;
    }
    return (0);
}

int ft_isnumber(char *str)
{
	int i = 0;

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
int ft_exit(char **argv, t_shell *shell)
{
	long long status;

	status = 1;
	ft_putstr_fd("exit\n", 2);
	if (!argv[1])
	{
		status = shell->exit_status;
	}
	else if (!ft_isnumber(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		status = 2;
	}
	else if (argv[2])
	{
		ft_putstr_fd("minishell: exit: Too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	else
		status = ft_atoi(argv[1]); // remplacer par un atoll car on peut quitter avec un code erreur au dessus de int

	// liberer la env aussi
	free_shell(shell);

	// quit avc le bon status
	exit((int)status);
}
