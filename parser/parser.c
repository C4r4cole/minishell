/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:53:29 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 12:50:21 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char **test_parser(char *input)
{
	char	**lexer;
	char	**tokens;
	
	lexer = input_splitter(input);
	tokens = quotes_management(lexer);
	return (tokens);
}
