/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:00:35 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 19:50:20 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	ft_path_error(t_shell *sh, t_cmd *cmds)
{
	free_envp(sh);
	if (cmds->to_pipe && sh->pipe_new)
		free(sh->pipe_new);
	if (cmds->from_pipe && sh->pipe_old)
		free(sh->pipe_old);
	free_single_cmd(cmds);
	ft_exit(0, 0, 1);
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
		ft_exit(126, 1, 0);
	}
	else if (!is_folder(path) && !is_file(path) && (ft_isrelative(cmds[0])))
		ft_putstr_fd("minishell: no such file or directory \"", 2);
	else if (is_folder(path) && ft_isrelative(cmds[0]))
	{
		ft_putstr_fd("minishell: prompt is a directory! \"", 2);
		ft_exit(126, 1, 0);
	}
	else
		ft_putstr_fd("minishell: command not found \"", 2);
	if (cmds[0])
		ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\"\n", 2);
	if (path && path != cmd->cmd[0])
		free(path);
	ft_path_error(sh, cmd);
}

static void	close_pipes(t_shell *sh, t_cmd *cmd)
{
	if (cmd->from_pipe)
		free(sh->pipe_old);
	if (cmd->to_pipe)
		free(sh->pipe_new);
}

void	handle_perm_error(t_cmd *cmd, t_shell *sh)
{
	(void)sh;
	ft_fprintf(2, "minishell: Permission denied or file does not exist!\n");
	if ((cmd->to_pipe || cmd->from_pipe) && !cmd->cmd && cmd->infile_error)
	{
		ft_exit(0, true, false);
	}
	else
		ft_exit(1, true, false);
	if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
	{
		close(sh->original_stdin);
		close(sh->original_stdout);
		free_envp(sh);
		if (!cmd->to_pipe || !cmd->from_pipe)
		{
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
			if (cmd->fd_out != -1)
				close(cmd->fd_out);
		}
		close_pipes(sh, cmd);
		free_single_cmd(cmd);
		ft_exit(0, 0, 1);
	}
}
