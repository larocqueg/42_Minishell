/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:09:10 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/03/19 12:23:04 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
		i += write(fd, str++, 1);
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
		i += write(1, str++, 1);
	return (i);
}
