/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:44:59 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/15 17:45:47 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **input_splitter(char *input)
{
	char	**input_splitted;
	int		i;
	int		j;
	
	input_splitted = ft_split(input, ' ');
	i = 0;
	while (input_splitted[i])
	{
		j = 0;
		while (input_splitted[i][j])
		{
			if (!(input_splitted[i][j] >= 'a' && input_splitted[i][j] <= 'z'))
			{
				//est-ce que tu pourrais plutot reprendre mon code te m'expliquer ce que je dois mettre ici stp
			}
			j++;
		}
		i++;
	}
}