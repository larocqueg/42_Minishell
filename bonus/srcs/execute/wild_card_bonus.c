/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:27:48 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/19 12:28:01 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_match(char *str, char *line)
{
	if (!*str && !*line)
		return (1);
	if (*str == '*')
	{
		if (ft_match(str + 1, line))
			return (1);
		if (*line && ft_match(str, line + 1))
			return (1);
	}
	else if (*str == *line)
		return (ft_match(str + 1, line + 1));
	return (0);
}

char	*get_dir(DIR *directory)
{
	char			*line;
	struct dirent	*entry;

	entry = readdir(directory);
	if (!entry)
		return (NULL);
	line = entry->d_name;
	if (!line)
		return (NULL);
	return (line);
}

char	*get_arg(DIR *directory, char *str)
{
	char	*line;

	while (1)
	{
		line = get_dir(directory);
		if (!line)
			return (NULL);
		if (ft_match(str, line))
			return (line);
	}
}

int	has_wildcard(char *str)
{
	int		i;
	bool	slash;
	bool	wild;

	wild = 0;
	slash = 0;
	i = 0;
	if (has_quotes(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			wild = 1;
		if (str[i] == '/')
			slash = 1;
		i++;
	}
	if (wild && !slash)
		return (1);
	return (0);
}
