/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:00:35 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 20:57:47 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_path_error(t_shell *sh, t_cmd *cmds)
{
	free_envp(sh);
	if (cmds->to_pipe)
		free(sh->pipe_new);
	if (cmds->from_pipe)
		free(sh->pipe_old);
	free_cmds(sh);
	ft_exit_status(0, 0, 1);
}

int	ft_isrelative(char *str)
{
	if (ft_strncmp("./", str, 2) == 0)
		return (1);
	else if (ft_strncmp("/", str, 1) == 0)
		return (1);
	else
		return (0);
}

void	ft_command_error(t_cmd *cmd, char *path, char **cmds, t_shell *sh)
{
	if (path && ((access(path, F_OK) == 0 && access(path, X_OK) != 0)
			|| is_character_device(path)))
	{
		ft_putstr_fd("minishell: permission denied: \"", 2);
		ft_exit_status(126, 1, 0);
	}
	else if (!is_folder(path) && !is_file(path) && (ft_isrelative(cmds[0])))
		ft_putstr_fd("minishell: no such file or directory \"", 2);
	else if (is_folder(path) && ft_isrelative(cmds[0]))
	{
		ft_putstr_fd("minishell: prompt is a directory! \"", 2);
		ft_exit_status(126, 1, 0);
	}
	else
		ft_putstr_fd("minishell: command not found \"", 2);
	if (cmds[0])
		ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\"\n", 2);
	if (path)
		free(path);
	ft_path_error(sh, cmd);
}

void	handle_perm_error(t_cmd *cmd)
{
	ft_fprintf(2, "minishell: Permission denied or file does not exist!\n");
	if ((cmd->to_pipe || cmd->from_pipe) && !cmd->cmd && cmd->infile_error)
		ft_exit_status(0, true, true);
	ft_exit_status(1, true, false);
	if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
		ft_exit_status(0, 0, 1);
}
