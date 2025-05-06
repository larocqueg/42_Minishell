/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:47:15 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
	free_all_cmds(sh, cmd);
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
	if (!perm_error(cmd) && ft_is_builtin(cmd->cmd) && ft_exit(0, 0, 0) != 141)
		exec_builtin(cmd, sh);
	else if (!perm_error(cmd))
	{
		ft_get_colors(cmd);
		if (cmd->from_pipe)
			usleep(10);
		exec_cmd(cmd, sh->envp, sh);
	}
	if (perm_error(cmd))
		handle_perm_error(cmd, sh);
}

static void	wait_for_pids(t_shell *sh, int count)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, child_signal_handler);
	while (i < count)
	{
		waitpid(sh->pids[i], &status, 0);
		if (WIFEXITED(status))
			ft_exit(WEXITSTATUS(status), true, false);
		else if (WIFSIGNALED(status))
			ft_exit(WTERMSIG(status) + 128, true, false);
		i++;
	}
	if (ft_exit(0, 0, 0) == 131)
		ft_fprintf(2, "Quit (core dumped)\n");
}

static void	execute_commands(t_shell *sh, t_cmd *cmd, int i, int pid)
{
	while (cmd)
	{
		pid = -1;
		if (!init_exec_commands(sh, cmd, &pid))
			return ;
		if (pid == 0 || pid == -1)
		{
			signal_reset();
			signal(SIGPIPE, child_signal_handler);
			handle_child(sh, cmd, 0, 0);
		}
		else if (pid != 0)
		{
			if (pid > 0)
				sh->pids[i++] = pid;
			ft_close_execute_pipes(cmd);
		}
		change_pipes(sh, cmd);
		cmd = cmd->next;
	}
	if (i > 0)
		wait_for_pids(sh, i);
}

void	execute(t_shell *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd;
	get_pids(sh, cmd);
	free_tokens(sh->token);
	execute_commands(sh, cmd, 0, -1);
	if (sh->pids != NULL)
		free(sh->pids);
	free_cmds(sh);
	free_pipes(sh);
}
