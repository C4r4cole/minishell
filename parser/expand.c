/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 14:24:30 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*str_append_char(char *str, char c)
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

char	*expand_one_dollar(char *input, int *index, t_shell *shell)
{
    int i;
    char *value;
	int start;
	char *name;
	t_env *envlist;

	i = *index;
    if (input[i] == '?')
	{
        (*index)++;
        return (ft_itoa(shell->exit_status));
    }
    if (!ft_isalpha(input[i]) && input[i] != '_')
        return ft_strdup("$");
    start = i;
    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
        i++;
    name = ft_substr(input, start, i - start);
    envlist = shell->envp_lst;
    value = ft_strdup("");
    while (envlist) {
        if (ft_strcmp(envlist->key, name) == 0)
		{
            free(value);
			if (envlist->value)
            	value = ft_strdup(envlist->value);
			else
				value = ft_strdup("");
            break;
        }
        envlist = envlist->next;
    }
    free(name);
    *index = i;
    return (value);
}
