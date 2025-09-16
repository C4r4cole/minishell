/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/16 12:42:37 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**add_split(char **string_to_subsplit, int *nb_splitted, char *start, int len)
{
	char	**new_split_tab;
	char	*special_character;
	
	new_split_tab = realloc(string_to_subsplit, sizeof(char *) * (*nb_splitted + 2));
	if (!new_split_tab)
		return (string_to_subsplit);
	special_character = ft_strndup(start, len);
	if (!special_character)
		return (new_split_tab);
	new_split_tab[*nb_splitted] = special_character;
	(*nb_splitted)++;
	new_split_tab[*nb_splitted] = NULL;
	return (new_split_tab);
}

char **input_splitter(char *input)
{
	char	**input_splitted;
	char	**final_split;
	int		count;
	int		start;
	int		i;
	int		j;
	
	input_splitted = ft_split(input, ' ');
	final_split = NULL;
	i = 0;
	count = 0;
	while (input_splitted[i])
	{
		j = 0;
		while (input_splitted[i][j])
		{
			if (is_special(input_splitted[i][j]))
			{
				final_split = add_split(final_split, &count, &input_splitted[i][j], 1);
				j++;
			}
			else
			{
				start = j;
				while (input_splitted[i][j] && !(is_special(input_splitted[i][j])))
					j++;
				final_split = add_split(final_split, &count, &input_splitted[i][j], j - start);
			}
		}
		i++;
	}
	return (final_split);
}