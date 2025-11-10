/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:49:39 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/10 21:09:24 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

void	skip_quotes(char *str, int *i, int *j, char *res)
{
	char	quote;

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

// int	str_has_quote(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
