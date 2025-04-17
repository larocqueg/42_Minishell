/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:47:15 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/17 18:45:44 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_get_colors(t_cmd *cmds)
{
	int	i;

	i = get_argc(cmds->cmd);
	if (i == 0)
		return ;
	if (ft_strncmp(cmds->cmd[0], "ls", 3) == 0
		|| ft_strncmp(cmds->cmd[0], "grep", 5) == 0)
		cmds->cmd = append_cmd(cmds->cmd, "--color=auto");
}

static void	handle_child(t_shell *sh, t_cmd *cmd, int outfd, int infd)
{
	outfd = get_fdout(cmd, sh);
	infd = get_fdin(cmd, sh);
	if (outfd != STDOUT_FILENO)
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		if (!cmd->heredoc)
			close(infd);
	}
	if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
		ft_free_child_pipes(sh);
	if (!perm_error(cmd) && ft_is_builtin(cmd->cmd))
		exec_builtin(cmd, sh);
	else if (!perm_error(cmd))
	{
		ft_get_colors(cmd);
		exec_cmd(cmd, sh->envp, sh);
	}
	if (perm_error(cmd))
		handle_perm_error(cmd, sh);
}

static void	handle_parent(int pid, t_cmd *cmd)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		ft_exit_status(WEXITSTATUS(status), true, false);
	}
	else if (WIFSIGNALED(status))
	{
		ft_exit_status(WTERMSIG(status) + 128, true, false);
	}
	if (ft_exit_status(0, 0, 0) == 131)
		ft_fprintf(2, "Quit (core dumped)\n");
}

static void	execute_commands(t_shell *sh, t_cmd *cmd)
{
	int		pid;
	int		status;

	while (cmd)
	{
		status = 0;
		pid = -1;
		if (!init_exec_commands(sh, cmd, &pid))
			return ;
		if (pid == 0 || pid == -1)
		{
			signal_default();
			signal(SIGPIPE, child_signal_handler);
			handle_child(sh, cmd, 0, 0);
		}
		else if (pid != 0)
			ft_close_execute_pipes(cmd);
		change_pipes(sh, cmd);
		cmd = cmd->next;
	}
	if (pid != 0 && pid != -1)
		handle_parent(pid, cmd);
}

void	execute(t_shell *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd;
	free_tokens(sh->token);
	execute_commands(sh, cmd);
	free_cmds(sh);
	free_pipes(sh);
}
