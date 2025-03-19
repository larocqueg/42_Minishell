/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 14:14:05 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char *av[], char **envp)
{
	//char	*prompt;
	char	*pwd;
	signal(SIGINT, signal_handler);
	pwd = malloc(sizeof(char) * 4096);
	(void)ac;
	(void)av;
	(void)envp;

	getcwd(pwd, 4096);
	pwd = ft_strrchr(pwd, '/');
	ft_strlcat(pwd++, " <$ ", 4096);

	while (1)
	{
		printf("\033[0;31m%s\033[0m", pwd);
		readline("");
	}
}
