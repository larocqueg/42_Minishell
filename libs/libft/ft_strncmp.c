/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:53:43 by gde-la-r          #+#    #+#             */
/*   Updated: 2024/10/30 11:45:11 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
#include "ft_atoi.c"
#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac == 4)
	{
		printf("%d\n", ft_strncmp(av[1], av[2], (size_t)ft_atoi(av[3])));
		return (0);
	}
	else if (ac > 4)
		printf("Too many arguments!\n");
	else
		printf("Missing command-line argument!\n");
	return (1);
}*/
