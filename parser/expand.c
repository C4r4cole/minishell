/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/21 17:46:22 by fmoulin          ###   ########.fr       */
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

static char	*append_char(char *str, char c)
{
	char tmp[2];
	char *joined;
	
	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(str, tmp);
	free(str);
	return (joined);
}

char *ft_strjoin_free(char *s1, char *s2)
{
	char *joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

char	*expand_dollar(char *token, t_env *env)
{
    // t_env	*current_env;
	// int		len;
	// char	*var_name;
	// char	*result;
	
    // if (!token || !is_dollar(token[0]))
	// 	return (ft_strdup(token));
    // len = ft_strlen(token);
    // current_env = env;
	// if (is_o_curly_bracket(token[1]) && is_c_curly_bracket(token[len - 1]))
	// 	var_name = ft_substr(token, 2, len - 3);
	// else
	// 	var_name = ft_substr(token, 1, len - 1);
    // while (current_env)
    // {
	// 	if (ft_strcmp(var_name, current_env->key) == 0)
	// 	{
	// 		result = ft_strdup(current_env->value);
	// 		free(var_name);
	// 		return (result);
	// 	}
	// 	current_env = current_env->next;
    // }
    // return (free(var_name), ft_strdup(""));
	
	char	*result;
	int		i;
	int		start;
	char	*var_name;
	char	*var_value;
	t_env	*tmp;

	result = ft_strdup("");
	i = 0;
	while (token[i])
	{
		if (is_dollar(token[i]))
		{
			i++;
			start = i;
			while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
				i++;
			var_name = ft_substr(token, start, i - start);
			var_value = ft_strdup("");
			tmp = env;
			while (tmp)
			{
				if (ft_strcmp(tmp->key, var_name) == 0)
				{
					free(var_value);
					var_value = ft_strdup(tmp->value);
					break ;
				}
				tmp = tmp->next;
			}
			result = ft_strjoin_free(result, var_value);
			free(var_name);
		}
		else
		{
			result = append_char(result, token[i]);
			i++;
		}
	}
	return (result);
}
