/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:04:01 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	is_character_device(const char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0)
	{
		return (S_ISCHR(st.st_mode));
	}
	return (0);
}

int	is_folder(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0)
	{
		return (S_ISDIR(st.st_mode));
	}
	return (0);
}

int	is_file(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0)
	{
		return (S_ISREG(st.st_mode));
	}
	return (0);
}

char	*path_finder(char *cmds, char **env)
{
	int		i;
	char	**paths;
	char	*part_path;
	char	*path;

	path = ft_get_env("PATH", env);
	if (!path)
		return (local_path_finder(ft_strjoin("./", cmds), true));
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmds);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

char	*local_path_finder(char *cmd, bool from_path_finder)
{
	char	*path;

	if (!cmd || !*cmd)
		return (NULL);
	path = ft_strdup(cmd);
	if (from_path_finder)
		free(cmd);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == 0 && (is_file(path)
			|| is_folder(path) || is_character_device(path)))
		return (path);
	free(path);
	return (NULL);
}
