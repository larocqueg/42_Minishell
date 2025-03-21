/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 13:54:39 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize(char *str)
{
	int	start = 0;
	int end = 0;
	while (str[end])
	{
		if (is_space(str[end])|| is_redirect(str[end]))
		{
			
		}
	}

}

