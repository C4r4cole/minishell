/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:26:30 by fmoulin           #+#    #+#             */
/*   Updated: 2025/09/16 12:39:54 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int len)
{
	char	*s_dup;
	int		i;

	i = 0;
	s_dup = malloc(sizeof(char) * (len + 1));
	if (!s_dup)
		return (NULL);
	while (s[i] && i < len)
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
