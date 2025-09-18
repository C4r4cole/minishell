/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/17 16:26:15 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_dollar(char c)
{
	return (c == '$');
}

int	is_question_mark(char c)
{
	return (c == '?');
}

int	is_double_quote(char c)
{
	return (c == '"');
}

int is_single_quote(char c)
{
	return (c == '\'');
}

int is_ampersand(char c)
{
	return (c == '&');
}

