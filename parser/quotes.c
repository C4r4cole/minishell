/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:05:13 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 16:21:44 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**quotes_management(char **final_split)
{
	char	**tokens;
	char	*joined;
	char 	*tmp;
	// char	*quoted;
	int		count;
	int		i;

	tokens = NULL;
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
				tmp = joined;
				joined = ft_strjoin(joined, final_split[i]);
				free(tmp);
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
			// quoted = ft_strjoin("\"", joined);
			// free(joined);
			// tmp = quoted;
			// quoted = ft_strjoin(quoted, "\"");
			// free(tmp);
			// tokens = add_split(tokens, &count, quoted, ft_strlen(quoted));
			// free(quoted);
			
			// ================================================================ //
			// ======== ENVOYER VERS EXPAND POUR GERER '$', '`' ET '\' ======== //
			// ================================================================ //
			
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
			// quoted = ft_strjoin("\"", joined);
			// free(joined);
			// tmp = quoted;
			// quoted = ft_strjoin(quoted, "\"");
			// free(tmp);
			// tokens = add_split(tokens, &count, quoted, ft_strlen(quoted));
			// free(quoted);
			
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