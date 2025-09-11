/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:56:38 by fmoulin           #+#    #+#             */
/*   Updated: 2025/04/29 10:14:38 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	unsigned char	c_cast;
	unsigned char	*s_cast;
	size_t			i;

	c_cast = c;
	s_cast = s;
	i = 0;
	while (i < size)
	{
		s_cast[i] = c_cast;
		i++;
	}
	return (s_cast);
}
