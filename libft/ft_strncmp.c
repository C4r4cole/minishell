/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:22:30 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/06 18:38:02 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] != '\0'
		&& (unsigned char)s2[i] != '\0' && i < size)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < size)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s1[] = "hello";
// 	char s2[] = "helio";

// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	return (0);
// }
