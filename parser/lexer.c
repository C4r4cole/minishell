/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/16 17:08:22 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**add_split(char **string_to_subsplit, int *nb_splitted, char *start, int len)
{
	char	**new_split_tab;
	char	*special_character;
	int		i;
	
	new_split_tab = malloc(sizeof(char *) * (*nb_splitted + 2));
	if (!new_split_tab)
		return (string_to_subsplit);
	i = 0;
	while (i < *nb_splitted)
	{
		new_split_tab[i] = string_to_subsplit[i];
		i++;
	}
	special_character = ft_strndup(start, len);
	if (!special_character)
	{
		free(new_split_tab);
		return (new_split_tab);
	}
	new_split_tab[*nb_splitted] = special_character;
	(*nb_splitted)++;
	new_split_tab[*nb_splitted] = NULL;
	free(string_to_subsplit);
	return (new_split_tab);
}

char **input_splitter(char *input)
{
	t_splitter result;
	int		i;
	int		j;
	
	result.input_split = ft_split(input, ' ');
	result.final_split = NULL;
	i = 0;
	result.count = 0;
	while (result.input_split[i])
	{
		j = 0;
		while (result.input_split[i][j])
		{
			if (is_special(result.input_split[i][j]) || is_redirection(result.input_split[i][j]))
			{
				result.final_split = add_split(result.final_split, &result.count, &result.input_split[i][j], 1);
				j++;
			}
			else
			{
				result.start = j;
				while (result.input_split[i][j] && (!(is_special(result.input_split[i][j])) && !is_redirection(result.input_split[i][j])))
					j++;
				result.final_split = add_split(result.final_split, &result.count, &result.input_split[i][result.start], j - result.start);
			}
		}
		i++;
	}
	return (result.final_split);
}
