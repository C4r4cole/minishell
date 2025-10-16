/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/16 17:47:15 by fmoulin          ###   ########.fr       */
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
	int		len;
	char	*var_name;
	char	*result;
	
    if (!token || !is_dollar(token[0]))
		return (ft_strdup(token));
    len = ft_strlen(token);
    current_env = env;
	if (is_o_curly_bracket(token[1]) && is_c_curly_bracket(token[len - 1]))
		var_name = ft_substr(token, 2, len - 3);
	else
		var_name = ft_substr(token, 1, len - 1);
    while (current_env)
    {
		if (ft_strcmp(var_name, current_env->key) == 0)
		{
			result = ft_strdup(current_env->value);
			free(var_name);
			return (result);
		}
		current_env = current_env->next;
    }
    return (free(var_name), ft_strdup(""));
}
