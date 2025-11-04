/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/04 18:10:36 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

void skip_quotes(char *str, int *i, int *j, char *res)
{
	char quote;
	
	quote = str[*i++];
	while (str[*i] && str[*i] != quote)
		res[*j++] = str[*i++];
	if (str[*i] == quote)
		i++;
}

int	redirection_type(char **tokens, int *i)
{
	int	type;
	
	type = get_redir_type(tokens[*i]);
	if (type == -1)
		return (0);
	return (type);
}

char	*redirection_file(char **tokens, int *i)
{
	char	*file;
	
	file = ft_strdup(tokens[*i + 1]);
	if (!file)
		return (0);
	return (file);
}
