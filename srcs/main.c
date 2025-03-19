/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 12:31:25 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char *av[], char **envp)
{
	char	*prompt;
	char	*pwd;

	pwd = malloc(sizeof(char) * 4096);
	(void)ac;
	(void)av;
	(void)envp;

	getcwd(pwd, 4096);
	pwd = strrchr(pwd, '/');
	strcat(pwd++, " <$ ");

	while (1)
	{
		printf("\033[0;31m%s\033[0m", pwd);
		prompt = readline(NULL);
	}
}
