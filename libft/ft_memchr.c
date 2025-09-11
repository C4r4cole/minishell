/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:09:51 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/06 18:53:03 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str[6] = "hello";
// 	int	c;

// 	c = 'l';
// 	printf("%s\n", (char *)ft_memchr(str, c, sizeof(str)));
// 	return (0);
// }
