/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:13:00 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/01 21:28:35 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cd(char **cmd, t_shell *sh)
{
	char	*path;
	char	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (cmd[1] == NULL)
	{

		home = ft_get_env("HOME", sh);
		if (!home)
		{
			ft_printf("minihell: cd: HOME not set"); //change exit code to 1
			return 1;
		}

		path = getcwd(NULL, 0);
		chdir(ft_get_env("HOME", sh)); // temos q fazer a get env!!!!!!!!!
		ft_change_var("PWD=", path, sh);
		ft_change_var("OLDPWD=", oldpwd, sh);
		free(path);
		return (1);
	}
	if (chdir(cmd[1]) == -1)
	{
		printf("minihell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	path = getcwd(NULL, 0);
	ft_change_var("PWD=", path, sh);
	ft_change_var("OLDPWD=", oldpwd, sh);
	free(path);
	return (1);
}
