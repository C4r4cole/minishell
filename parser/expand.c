/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/02 17:28:29 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
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
	// printf("Ajout ou update : %s=%s\n", key, value);
}

char	*expand_dollar(char *token, t_env *env)
{
    t_env	*current_env;
    
    if (!is_dollar(token[0]))
        return (ft_strdup(token));
    
    current_env = env;
    while (current_env)
    {
        if (ft_strlen(&token[1]) == ft_strlen(current_env->key) && 
            !ft_strncmp(&token[1], current_env->key, ft_strlen(current_env->key)))
            return (ft_strdup(current_env->value));
        current_env = current_env->next;
    }
    return (ft_strdup(""));
}
