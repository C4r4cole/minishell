/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:06:48 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/10/29 11:02:00 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

t_env	*env_list_from_envp(char **envp)
{
	t_env	*head;
	t_env	*tail;
	int		i;
	char	*equal;
	int		key_len;
	char	*key;
	char	*value;
	t_env	*new;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp && envp[i])
	{
		// Découpe la variable en key et value
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue ;
		}
		key_len = equal - envp[i];
		key = ft_substr(envp[i], 0, key_len);
		value = ft_strdup(equal + 1);
		new = ft_envnew(key, value);
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		i++;
	}
	return (head);
}

void	env_update_or_add(t_env **lst, char *key, char *value)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value ? ft_strdup(value) : NULL;
			return ;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(lst, ft_envnew(ft_strdup(key),
			value ? ft_strdup(value) : NULL));
}
int	is_valid_env_name(const char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	env_remove(t_env **lst, char *key)
{
	t_env *prev;
	t_env *tmp;

	prev = NULL;
	tmp = *lst;
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
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}