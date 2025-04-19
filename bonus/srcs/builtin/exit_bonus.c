/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:28:58 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 16:48:04 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_is_numeric(char **cmd)
{
	long long	num;
	int			i;

	i = 0;
	if (!cmd[1][0])
		return (0);
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
			return (0);
		i++;
	}
	num = ft_atoll(cmd[1]);
	if (num == LLONG_MAX && ft_strncmp("9223372036854775807", cmd[1], 20) != 0)
		return (0);
	if (num == LLONG_MAX && ft_strncmp("+9223372036854775807", cmd[1], 21) != 0)
		return (0);
	if (num == LLONG_MIN && ft_strncmp("-9223372036854775808", cmd[1], 21) != 0)
		return (0);
	return (1);
}

void	ft_free_exit(t_shell *sh)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_fprintf(2, "exit\n");
	free_envp(sh);
	free_cmds(sh);
	close(sh->original_stdin);
	close(sh->original_stdout);
	if (sh->heredoc_count > 0)
		free(sh->heredoc_pipes);
	rl_clear_history();
}

void	exec_exit(t_shell *sh, t_cmd *cmds)
{
	int				argc;
	unsigned char	exit_code;

	argc = get_argc(cmds->cmd);
	if (argc == 1)
	{
		ft_free_exit(sh);
		ft_exit(0, 0, 1);
	}
	else if (!ft_is_numeric(cmds->cmd))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", cmds->cmd[1]);
		ft_free_exit(sh);
		ft_exit(2, 1, 1);
	}
	if (argc > 2)
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		ft_exit(1, 1, 0);
		return ;
	}
	exit_code = ft_atoll(cmds->cmd[1]);
	ft_free_exit(sh);
	ft_exit(exit_code, 1, 1);
}
