/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:42:09 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 17:26:03 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_env_value(char *name, t_shell *shell)
{
	t_env	*envlist;
	char	*value;

	envlist = shell->envp_lst;
	value = ft_strdup("");
	while (envlist)
	{
		if (!ft_strcmp(envlist->key, name))
		{
			free(value);
			if (envlist->value)
				value = ft_strdup(envlist->value);
			else
				value = ft_strdup("");
			break ;
		}
		envlist = envlist->next;
	}
	return (value);
}

char	*expand_one_dollar(char *input, int *index, t_shell *shell)
{
	int		i;
	int		start;
	char	*name;
	char	*value;

	i = *index;
	if (input[i] == '?')
		return ((*index)++, ft_itoa(shell->exit_status));
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (ft_strdup("$"));
	start = i;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	name = ft_substr(input, start, i - start);
	value = get_env_value(name, shell);
	free(name);
	*index = i;
	return (value);
}

// char	*expand_one_dollar(char *input, int *index, t_shell *shell)
// {
// 	int		i;
// 	char	*value;
// 	int		start;
// 	char	*name;
// 	t_env	*envlist;

// 	i = *index;
// 	if (input[i] == '?')
// 	{
// 		(*index)++;
// 		return (ft_itoa(shell->exit_status));
// 	}
// 	if (!ft_isalpha(input[i]) && input[i] != '_')
// 		return (ft_strdup("$"));
// 	start = i;
// 	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
// 		i++;
// 	name = ft_substr(input, start, i - start);
// 	envlist = shell->envp_lst;
// 	value = ft_strdup("");
// 	while (envlist)
// 	{
// 		if (ft_strcmp(envlist->key, name) == 0)
// 		{
// 			free(value);
// 			if (envlist->value)
// 				value = ft_strdup(envlist->value);
// 			else
// 				value = ft_strdup("");
// 			break ;
// 		}
// 		envlist = envlist->next;
// 	}
// 	free(name);
// 	*index = i;
// 	return (value);
// }

int	expand_and_join(t_splitter *initialized, char *input, t_shell *shell)
{
	char	*expanded;
	char	*joined;

	if (is_dollar(input[initialized->i]))
	{
		initialized->i++;
		expanded = expand_one_dollar(input, &initialized->i, shell);
		joined = ft_strjoin(initialized->buf, expanded);
		free(initialized->buf);
		free(expanded);
		initialized->buf = joined;
		return (1);
	}
	return (0);
}
