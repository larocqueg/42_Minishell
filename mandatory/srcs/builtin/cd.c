/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:13:00 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/23 19:29:25 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_error(t_shell *sh, char *error, char *cmd)
{
	(void)sh;
	if (!cmd)
		ft_fprintf(2, "%s", error);
	else
		ft_fprintf(2, "%s directory \"%s\"\n", error, cmd);
	ft_exit(1, 1, 0);
	return (1);
}

static void	change_var(char *path, char *old_pwd, t_shell *sh)
{
	if (ft_get_env("PWD", sh->envp))
		ft_change_var("PWD=", path, sh->envp);
	if (ft_get_env("OLDPWD", sh->envp))
		ft_change_var("OLDPWD=", old_pwd, sh->envp);
}

int	get_argc(char **cmd)
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

	if (get_argc(cmd) > 2)
		return (cd_error(sh, "minishell: cd: Too many arguments!\n", NULL));
	oldpwd = getcwd(NULL, 0);
	if (cmd[1] == NULL || (get_argc(cmd) > 1 && cmd[1][0] == '\0'))
	{
		home = ft_get_env("HOME", sh->envp);
		if (!home)
			return (free(oldpwd), cd_error(sh, HOME_ERROR, NULL));
		chdir(ft_get_env("HOME", sh->envp));
		path = getcwd(NULL, 0);
		change_var(path, oldpwd, sh);
		ft_exit(0, 1, 0);
		return (free(path), free(oldpwd), 1);
	}
	else if (chdir(cmd[1]) == -1)
		return (free(oldpwd), cd_error(sh, "minishell: cd: No such", cmd[1]));
	path = getcwd(NULL, 0);
	change_var(path, oldpwd, sh);
	ft_exit(0, 1, 0);
	return (free(path), free(oldpwd), 1);
}
