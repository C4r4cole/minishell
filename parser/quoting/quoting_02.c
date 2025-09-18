/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:25:45 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:28:37 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int is_redirection_in(char c)
{
	return (c == REDIRECTION_IN);
}

int	is_redirection_out(char c)
{
	return (c == REDIRECTION_OUT);
}

int is_semicolon(char c)
{
	return (c == SEMI_COLON);
}

int is_opening_parenthesis(char c)
{
	return (c == OPENING_PARENTHESIS);
}

int is_closing_parenthesis(char c)
{
	return (c == CLOSING_PARENTHESIS);
}

