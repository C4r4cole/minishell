/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:05:13 by fmoulin           #+#    #+#             */
/*   Updated: 2025/10/22 12:16:44 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**double_quote_management(char **final_split, t_shell *shell, char **tokens, int *count, int *i)
{
	char	*joined;
	char	*expanded;
	char 	*tmp;

	(*i)++;
	joined = ft_strdup("");
	while (final_split[*i] && !(is_double_quote(final_split[*i][0]) && final_split[*i][1] == '\0'))
	{
		expanded = expand_dollar(final_split[*i], shell);
		tmp = joined;
		joined = ft_strjoin(joined, expanded);
		free(tmp);
		free(expanded);
		if (final_split[*i + 1] && !(is_double_quote(final_split[*i + 1][0]) && final_split[*i + 1][1] == '\0'))
		{
			tmp = joined;
			joined = ft_strjoin(joined, " ");
			free(tmp);
		}
		(*i)++;
	}
	if (final_split[*i])
		(*i)++;
	tokens = add_split(tokens, count, joined, ft_strlen(joined));
	if (!tokens)
		return (NULL);
	return (free(joined), tokens);
}

char	**single_quote_management(char **final_split, char **tokens, int *count, int *i)
{
	char	*joined;
	char 	*tmp;
	
	(*i)++;
	joined = ft_strdup("");
	while (final_split[*i] && !(is_single_quote(final_split[*i][0]) && final_split[*i][1] == '\0'))
	{
		tmp = joined;
		joined = ft_strjoin(joined, final_split[*i]);
		free(tmp);
		if (final_split[*i + 1] && !(is_single_quote(final_split[*i + 1][0]) && final_split[*i + 1][1] == '\0'))
		{
			tmp = joined;
			joined = ft_strjoin(joined, " ");
			free(tmp);
		}
		(*i)++;
	}
	if (final_split[*i])
		(*i)++;
	tokens = add_split(tokens, count, joined, ft_strlen(joined));
	if (!tokens)
		return (NULL);
	free(joined);
	return (tokens);
}

char	**quotes_management(char **final_split, t_shell *shell)
{
	char	**tokens;
	char	*expanded;
	int		count;
	int		i;

	tokens = NULL;
	count = 0;
	i = 0;
	
	while (final_split[i])
	{
		if (is_double_quote(final_split[i][0]) && final_split[i][1] == '\0')
		{
			tokens = double_quote_management(final_split, shell, tokens, &count, &i);
		}
		else if (is_single_quote(final_split[i][0]) && final_split[i][1] == '\0')
		{
			tokens = single_quote_management(final_split, tokens, &count, &i);
		}
		else
		{
			expanded = expand_dollar(final_split[i], shell);
			tokens = add_split(tokens, &count, expanded, ft_strlen(expanded));
			free(expanded);
			if (!tokens)
				return (NULL);
			i++;
		}
	}
	return (tokens);
}
