/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:05:13 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/24 14:26:19 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**quotes_management(char **final_split)
{
	char	**tokens;
	char	*joined;
	char 	*tmp;
	t_env	*env;
	t_env	*env_lst;
	char	*var_name;
	char	*value;
	// char	*quoted;
	int		count;
	int		i;

	tokens = NULL;
	env = NULL;
	env_lst = NULL;
	count = 0;
	i = 0;
	
	while (final_split[i])
	{
		if (is_double_quote(final_split[i][0]) && final_split[i][1] == '\0')
		{
			i++;
			joined = ft_strdup("");
			while (final_split[i] && !(is_double_quote(final_split[i][0]) && final_split[i][1] == '\0'))
			{
				// ================================================================ //
				// ======== ENVOYER VERS EXPAND POUR GERER '$', '`' ET '\' ======== //
				// ================================================================ //
				
				if (is_dollar(final_split[i][0])) // || is_backtick(final_split[i][0]) || is_backslash(final_split[i][0])
				{
					var_name = &final_split[i][1];
					value  = getenv(var_name);
					if (!value)
						value = "";
					env = ft_envnew(final_split[i], value);
					ft_envadd_back(&env_lst, env);
					tmp = joined;
					joined = ft_strjoin(joined, env->value);
					free(tmp);
				}
				else
				{
					tmp = joined;
					joined = ft_strjoin(joined, final_split[i]);
					free(tmp);
				}
				if (final_split[i + 1] && !(is_double_quote(final_split[i + 1][0]) && final_split[i + 1][1] == '\0'))
				{
					tmp = joined;
					joined = ft_strjoin(joined, " ");
					free(tmp);
				}
				i++;
			}
			if (final_split[i])
				i++;
			tokens = add_split(tokens, &count, joined, ft_strlen(joined));
			free(joined);
		}
		else if (is_single_quote(final_split[i][0]) && final_split[i][1] == '\0')
		{
			i++;
			joined = ft_strdup("");
			while (final_split[i] && !(is_single_quote(final_split[i][0]) && final_split[i][1] == '\0'))
			{
				tmp = joined;
				joined = ft_strjoin(joined, final_split[i]);
				free(tmp);
				if (final_split[i + 1] && !(is_single_quote(final_split[i + 1][0]) && final_split[i + 1][1] == '\0'))
				{
					tmp = joined;
					joined = ft_strjoin(joined, " ");
					free(tmp);
				}
				i++;
			}
			if (final_split[i])
				i++;			
			tokens = add_split(tokens, &count, joined, ft_strlen(joined));
			free(joined);
		}
		else
		{
			tokens = add_split(tokens, &count, final_split[i], ft_strlen(final_split[i]));
			i++;
		}
	}
	return (tokens);
}