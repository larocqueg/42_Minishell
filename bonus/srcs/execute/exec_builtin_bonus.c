/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:46:06 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:46:07 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	free_builtin(t_cmd *cmd, t_shell *sh)
{
	if (cmd->to_pipe || cmd->from_pipe)
	{
		close(sh->original_stdin);
		close(sh->original_stdout);
		free_envp(sh);
		if (cmd->to_pipe)
			free(sh->pipe_new);
		if (cmd->from_pipe)
			free(sh->pipe_old);
		free_cmds(sh);
		if (sh->heredoc_count > 0)
			free(sh->heredoc_pipes);
		ft_exit(0, 0, 1);
	}
	else
		return ;
}

void	exec_builtin(t_cmd *cmd, t_shell *sh)
{
	if (!cmd->cmd || !*cmd->cmd)
	{
		if (cmd->to_pipe || cmd->from_pipe)
			ft_exit(0, 0, 1);
		return ;
	}
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		exec_exit(sh, cmd);
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		exec_cd(cmd->cmd, sh);
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		exec_export(sh, cmd);
	if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		exec_pwd(cmd);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		exec_echo(cmd);
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		exec_env(sh, cmd);
	if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		exec_unset(sh, cmd->cmd);
	if (cmd->fd_in != -1)
		dup2(sh->original_stdin, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(sh->original_stdout, STDOUT_FILENO);
	free_builtin(cmd, sh);
}

int	ft_is_builtin(char **cmds)
{
	if (!cmds || !*cmds)
		return (0);
	if (ft_strncmp(cmds[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmds[0], "unset", 6) == 0)
		return (1);
	return (0);
}
