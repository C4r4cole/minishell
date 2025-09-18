/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:25:45 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/17 16:26:39 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int is_redirection_in(char c)
{
	return (c == '<');
}

int	is_redirection_out(char c)
{
	return (c == '>');
}

int is_semicolon(char c)
{
	return (c == ';');
}

int is_opening_parenthesis(char c)
{
	return (c == '(');
}

int is_closing_parenthesis(char c)
{
	return (c == ')');
}

