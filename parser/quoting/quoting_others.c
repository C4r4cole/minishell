/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsedjal <ilsedjal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:35:56 by fmoulin           #+#    #+#             */
/*   Updated: 2025/11/06 14:07:25 by ilsedjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_pipe(char c)
{
	return (c == PIPE);
}

int	is_space(char c)
{
	return (c == SPACE);
}

int	is_tab(char c)
{
	return (c == TAB);
}

int	is_dollar(char c)
{
	return (c == DOLLAR);
}
