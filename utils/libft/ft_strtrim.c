/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:58:21 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/07 12:48:38 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	first_dif(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (is_in_set(set, s1[i]) != 1)
			return (i);
		i++;
	}
	return (i);
}

static int	first_dif_reverse(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0)
	{
		i--;
		if (is_in_set(set, s1[i]) != 1)
			return (i);
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	int		start;
	int		i;
	char	*new;

	i = 0;
	start = first_dif(s1, set);
	if (s1[start] == 0)
		return (ft_strdup(""));
	size = first_dif_reverse(s1, set) - start + 1;
	new = ft_substr(s1, start, size);
	return (new);
}

// #include <stdio.h>

// int	main(void)
// {
// 		char	s1[] = "\n\n\nHello \t  Please\n Trim me !\n   \n \n \";
// 		char	set[] = " \n\t";

// 		printf("%s\n", ft_strtrim(s1, set));
// 		return (0);
// 	}
