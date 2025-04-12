/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:28:58 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/12 19:51:05 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char **cmd)
{

}

void	exec_exit(t_shell *sh, t_cmd *cmds)
{
	if (cmds->cmd[1] == NULL)
	{
		free_envp(sh);
		free_cmds(sh);
		close(sh->original_stdin);
		close(sh->original_stdout);
		rl_clear_history();
		ft_printf("exit\n");
		ft_exit_status(0, 0, 1);
	}


}
/*
rafaelfe@c1r9s9:~$ exit asdasd
exit
bash: exit: asdasd: numeric argument required
➜  ~ echo $?
2  // exited

afaelfe@c1r9s9:~$ exit 12319321938219382193821398
exit
bash: exit: 12319321938219382193821398: numeric argument required
➜  ~ echo $?
2 // exited

rafaelfe@c1r9s9:~$ exit 123 asdasd
exit
bash: exit: too many arguments
rafaelfe@c1r9s9:~$ echo $?
1 // did not exit

rafaelfe@c1r9s9:~$ exit asijdasi 123
exit
bash: exit: asijdasi: numeric argument required
-> ~ echo $?
2 // exited









*/
