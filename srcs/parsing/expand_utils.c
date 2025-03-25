/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:28:46 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/25 16:46:49 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_insertstr(char	*string, int index, char *substr)
{
	int		i;
	char	*part_one;
	char	*result;

	i = 0;
	if (!substr || !*substr)
		return (string);
	result = malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(substr) + 1));
	if (!result)
		return (NULL);

	while(string[i])
	{

	}

}
