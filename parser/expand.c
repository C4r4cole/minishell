/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/29 16:45:09 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_env	*ft_envnew(char *envp)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		i;
	
	i = 0;
	while (envp[i] && envp[i] != '=')
	i++;
	key = ft_strndup(envp, i);
	new = malloc(sizeof(t_env));
	if (!new)
	return (NULL);
	value  = getenv(key);
	if (!value)
	value = "";
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*current_elem;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current_elem = *lst;
	while (current_elem->next != NULL)
	{
		current_elem = current_elem->next;
	}
	current_elem->next = new;
}

t_env	*stored_env(char **envp)
{
	t_env	*env_lst;
	t_env	*new_env;
	int		i;

	i = 0;
	while (envp[i])
	{
		new_env = ft_envnew(envp[i]);
		ft_envadd_back(&env_lst, new_env);
		i++;
	}
	return (env_lst);
}
