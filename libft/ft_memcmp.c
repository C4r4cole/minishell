/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:51:08 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/06 19:11:07 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t	i;
	int		res;

	i = 0;
	if (size == 0)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]
		&& i < size - 1)
	{
		i++;
	}
	res = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1 = "abcdefghij";
// 	char	*s2 = "abcdefgxyz";

// 	printf("%d\n", memcmp(s1, s2, 7));
// 	printf("%d\n", ft_memcmp(s1, s2, 7));
// 	return (0);
// }
