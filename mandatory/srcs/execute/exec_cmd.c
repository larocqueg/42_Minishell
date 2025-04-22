/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:21:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:07:17 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve_error(t_shell *sh, char *path)
{
	ft_fprintf(2, "cannot execute '%s'\n", path);
	free_cmds(sh);
	free_envp(sh);
	free(path);
	ft_exit(8, 1, 1);
}

void	close_cmd_fds(t_cmd *cmd)
{
	bool	pipe;

	pipe = false;
	if (cmd->to_pipe || cmd->from_pipe)
		pipe = true;
	if (pipe)
	{
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		if (cmd->fd_in != -1 && !cmd->heredoc)
			close(cmd->fd_in);
	}
}

void	exec_cmd(t_cmd *cmds, char **env, t_shell *sh)
{
	char	*path;

	ft_exit(127, 1, 0);
	close(sh->original_stdin);
	close(sh->original_stdout);
	if (!cmds->cmd || !*cmds->cmd)
	{
		free_single_cmd(cmds);
		free_envp(sh);
		ft_exit(0, 1, 1);
	}
	path = NULL;
	if (ft_strncmp("./", cmds->cmd[0], 2) == 0
		|| ft_strncmp("/", cmds->cmd[0], 1) == 0)
		path = local_path_finder(cmds->cmd[0], false);
	else if (cmds->cmd[0] && !is_folder(cmds->cmd[0]))
		path = path_finder(cmds->cmd[0], env);
	else
		path = cmds->cmd[0];
	if (!path || access(path, X_OK) != 0 || is_folder(path)
		|| is_character_device(path))
		ft_command_error(cmds, path, cmds->cmd, sh);
	execve(path, cmds->cmd, env);
	ft_execve_error(sh, path);
}
