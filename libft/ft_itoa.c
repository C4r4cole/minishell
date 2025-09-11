/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:26:24 by fmoulin           #+#    #+#             */
/*   Updated: 2025/05/07 14:05:45 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_positive(int n)
{
	if (n == FT_INT_MIN)
	{
		return (n = (unsigned int)(- (n + 1) + 1));
	}
	else
	{
		return (n = (unsigned int)(-n));
	}
}

static int	count_nbr(int n)
{
	int				count;
	unsigned int	nb;

	count = 0;
	nb = 0;
	if (n == 0)
		count = 1;
	else if (n < 0)
	{
		nb = to_positive(n);
		count = 1;
	}
	else
		nb = (unsigned int) n;
	while (nb > 0)
	{
		nb = (unsigned int)(nb / 10);
		count ++;
	}
	return (count);
}

static char	*fill_tab(char *tab, int n, int count)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n = to_positive(n);
		tab[0] = '-';
	}
	while ((unsigned int)n > 9)
	{
		tab[count - i++] = ((unsigned int)n % 10) + 48;
		n = (unsigned int)n / 10;
	}
	if ((unsigned int)n <= 9)
		tab[count - i++] = ((unsigned int)n % 10) + 48;
	tab[count] = '\0';
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		count;

	count = count_nbr(n);
	tab = malloc(sizeof(char) * (count + 1));
	if (!tab)
		return (NULL);
	return (fill_tab(tab, n, count));
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	n;

// 	n = 1000034;
// 	printf("%s\n", ft_itoa(n));	
// 	return (0);
// }