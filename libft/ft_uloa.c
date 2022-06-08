/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uloa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:11:15 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/08 14:00:00 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stddef.h>

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_array(char *str, int nbr, size_t len)
{
	while (nbr > 0)
	{
		str[len] = '0' + (nbr % 10);
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

static int	ft_absolute(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_uloa(unsigned long ul)
{
	size_t	len;
	char	*str;
	int		nbr;
	int		n;

	n = (int)ul;
	len = ft_intlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	nbr = ft_absolute(n);
	return (ft_array(str, nbr, len));
}
