/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:47 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/18 17:27:53 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_dollar(char c)
{
	return (c == DOLLAR);
}

int	is_question_mark(char c)
{
	return (c == QUESTION_MARK);
}

int	is_double_quote(char c)
{
	return (c == DOUBLE_QUOTE);
}

int is_single_quote(char c)
{
	return (c == SINGLE_QUOTE);
}

int is_ampersand(char c)
{
	return (c == AMPERSAND);
}

