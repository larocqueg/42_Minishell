/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:07:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 02:37:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cli_pwd(t_shell *sh)
{
	char	*pwd;
	char	*cli_str;
	char	*temp;

	pwd = getcwd(NULL, 4096);
	if (ft_strncmp(getenv("HOME"), pwd, ft_strlen(pwd)) == 0)
	{
		cli_str = ft_strdup("~/ $< ");
	}
	else
	{
		temp = ft_strrchr(pwd, '/');
		cli_str = ft_strjoin(temp + 1, " $< " );
	}

	sh->cli_text = ft_strjoin(PROGRAM_NAME, cli_str);
	free(cli_str);
	free(pwd);
}
