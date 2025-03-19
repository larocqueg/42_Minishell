/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 19:47:18 by rafaelfe         ###   ########.fr       */
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

char	*append_cmd(char *path, char *cmd)
{
	char	*temp;

	temp = ft_strjoin(path, cmd);
	free(path);
	return (temp);
}
char	*check_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);

	while(envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

char **ft_split_path(char *env_path, char *cmd)
{
	char	**split_path;
	char	*slashcmd;
	int	i;

	slashcmd = ft_strjoin("/", cmd);
	split_path = ft_split(env_path, ':');
	i = 0;
	while (split_path[i])
	{
		split_path[i] = append_cmd(split_path[i], slashcmd);
		i++;
	}
	free(slashcmd);
	return (split_path);

}

char *check_cmdpath(char **split_path, char **pwdpath)
{
	int		i;
	char	*valid_path;

	valid_path = NULL;
	i = 0;
	while (split_path && split_path[i])
	{
		if (access(split_path[i], F_OK | X_OK) == 0)
			valid_path = split_path[i];
		i++;
	}
	if (!valid_path)
	{
		i = 0;
		while (pwdpath[i])
		{
			if (access(pwdpath[i], F_OK | X_OK) == 0)
				valid_path = pwdpath[i];
			i++;
		}
	}
	return (valid_path);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while(*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

void	handle_prompt(char *prompt, char **envp)
{
		char	*path;
		char	*pwd;
		char **cmd;
		char **split_path;
		char **pwdpath;

		int pid;
		if (prompt == NULL || prompt[0] == '\0' || only_spaces(prompt))
			return;
		pwd = NULL;
		split_path = NULL;
		cmd = ft_split(prompt, ' ');
		pwd = getcwd(pwd, 4096);
		if (check_cmd(cmd, envp))
			return ;
		pid = fork();

		if (pid != 0)
		{
			waitpid(pid, NULL, 0);
			return ;
		}
		path = check_envp(envp);
		if (path)
		{
			split_path = ft_split_path(path, cmd[0]);
		}
		pwdpath = ft_split_path(pwd, cmd[0]);
		path = check_cmdpath(split_path, pwdpath);
		if (!path)
		{

			ft_printf("testshell: %s: command not found\n", cmd[0]);
			exit(1);
		}
		else
			execve(path, cmd, envp);

}
int	main(int ac, char *av[], char **envp)
{
	char	*prompt;
	char	*pwd;
	char	*name;

	signal(SIGINT, signal_handler);
	pwd = malloc(sizeof(char) * 4096);
	(void)ac;
	(void)av;

	while (1)
	{
		getcwd(pwd, 4096);
		pwd = ft_strrchr(pwd, '/');
		ft_strlcat(++pwd, " ", 4096 );
		name = ft_strjoin(pwd, PROGRAM_NAME);
		prompt = readline(name);
		handle_prompt(prompt, envp);
	}

}
