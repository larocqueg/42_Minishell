/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:13:00 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:48 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_error(t_shell *sh, char *error, char *cmd)
{
	if (!cmd)
		ft_fprintf(2, "%s", error);
	else
		ft_fprintf(2, "%s directory \"%s\"\n", error, cmd);
	ft_exit_status(1, 1, 0);
	return (1);
}

static void	change_var(char *path, char *old_pwd, t_shell *sh)
{
	ft_change_var("PWD=", path, sh->envp);
	ft_change_var("OLDPWD=", old_pwd, sh->envp);
}

static int	get_cd_args(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	exec_cd(char **cmd, t_shell *sh)
{
	char	*path;
	char	*home;
	char	*oldpwd;

	if (get_cd_args(cmd) == 3)
		return (cd_error(sh, "minishell: cd: Too many arguments!\n", NULL));
	oldpwd = getcwd(NULL, 0);
	if (cmd[1] == NULL)
	{
		home = ft_get_env("HOME", sh->envp);
		if (!home)
			return (cd_error(sh, "minishell: cd: HOME not set\n", NULL));
		path = getcwd(NULL, 0);
		chdir(ft_get_env("HOME", sh->envp));
		change_var(path, oldpwd, sh);
		ft_exit_status(0, 1, 0);
		return (free(path), 1);
	}
	else if (chdir(cmd[1]) == -1)
		return (cd_error(sh, "minishell: cd: No such file or", cmd[1]));
	path = getcwd(NULL, 0);
	change_var(path, oldpwd, sh);
	ft_exit_status(0, 1, 0);
	return (free(path), 1);
}
