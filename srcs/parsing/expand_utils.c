/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:28:46 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/25 20:19:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_insertstr(char	*string, int index, char *substr)
{
	int		total_len;
	char	*after_str;
	char	*result;

	if (!substr || !*substr)
		return (string);

	total_len = ft_strlen(string) + ft_strlen(substr) + 1;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	after_str = NULL;
	if (index <= ft_strlen(string))
		after_str = string + index;
	ft_strlcpy(result, string, index + 1);
	ft_strlcat(result, substr, total_len);
	ft_strlcat(result, after_str, total_len);

	return (result);

}
