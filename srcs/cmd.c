/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:54:59 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 18:49:01 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cd(char **cmd)
{
	if (cmd[1] == NULL)
	{
		chdir(getenv("HOME"));
		return 1;
	}
	if (chdir(cmd[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		return 1;
	}
	return 1;
}


int	exec_pwd(char **cmd)
{
	char *pwd;
	pwd = NULL;
	if (cmd[1] != NULL)
	{
		printf("pwd: too many arguments!\n");
		return 1;
	}
	else
	{
		pwd =  getcwd(pwd, 4096);
		printf("%s\n", pwd);
		free(pwd);
	}
	return 1;
}

int	exec_echo(char **cmd, char *prompt)
{
	bool single_quotes = true;
	char *variable;
	char *variableresult;
	char *temp;
	char final = '\n';
	int	i = 1;
	if (!cmd[i])
		return (printf("\n"));
	if (ft_strncmp("-n", cmd[i], 3) == 0)
	{
		i++;
		final = '\0';
	}
	while (cmd[i])
	{	if (cmd[i][0] != '\'' && cmd[i][ft_strlen(cmd[i]) - 1] != '\'')
		{
			temp = ft_strtrim(cmd[i], "\"");
			free (cmd[i]);
			cmd[i] = temp;
			if ((variable = ft_strrchr(cmd[i], '$')))
			{
				if ((variableresult = getenv(variable + 1)) && variableresult != NULL)
					printf("%s", variableresult );
			}
			else
				printf("%s", cmd[i]);
		}
		else if (single_quotes)
		{
			cmd[i] = ft_strtrim(cmd[i], "\'");
			printf("%s", cmd[i]);
		}
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	(void)prompt;
	return (printf("%c", final));
}

int	check_cmd(char **cmd, char *prompt)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return(exec_echo(cmd, prompt));
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return(exec_cd(cmd));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (exec_pwd(cmd));
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		exit(1);
	return 0;
}
