/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:28:46 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/26 16:50:50 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_insertstr(char	*string, int index, char *substr)
{
	int		total_len;
	char	*after_str;
	char	*result;
	int		substr_len;

	total_len = ft_strlen(string) + ft_strlen(substr) + 1;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	after_str = NULL;

	ft_strlcpy(result, string, index);
	while(ft_isalnum(string[index]) || string[index] == '_')
		index++;
	if (string[index] == '?' && string[index - 1] == '$')
		index++;
	if (index <= ft_strlen(string))
		after_str = string + index;
	if (ft_strlen(substr) > 0)
		ft_strlcat(result, substr, total_len);
	ft_strlcat(result, after_str, total_len);

	return (result);

}
