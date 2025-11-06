/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:06:48 by ilsedjal          #+#    #+#             */
/*   Updated: 2025/11/05 16:16:40 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_header.h"

t_env	*env_create_node_from_line(char *line)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*node;

	eq = ft_strchr(line, '=');
	if (!eq)
		return (NULL);
	key = ft_substr(line, 0, eq - line);
	value = ft_strdup(eq + 1);
	node = ft_envnew(key, value);
	return (node);
}

t_env	*env_list_from_envp(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = env_create_node_from_line(envp[i]);
		if (node)
		{
			if (!head)
				head = node;
			else
				tail->next = node;
			tail = node;
		}
		i++;
	}
	return (head);
}

void	env_update_or_add(t_env **lst, char *key, char *value)
{
	t_env	*tmp;
	char	*new_value;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	if (value)
		new_value = ft_strdup(value);
	else
		new_value = NULL;
	ft_envadd_back(lst, ft_envnew(ft_strdup(key), new_value));
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

void	env_remove(t_env **lst, char *key)
{
	t_env	*prev;
	t_env	*tmp;

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
