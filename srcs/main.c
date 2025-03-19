/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 16:21:04 by rafaelfe         ###   ########.fr       */
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
char *check_cmdpath(char **split_path)
{
	int		i;
	char	*valid_path;

	valid_path = NULL;
	i = 0;
	while (split_path[i])
	{
		if (access(split_path[i], F_OK | X_OK) == 0)
			valid_path = split_path[i];
		i++;
	}
	return (valid_path);
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

void	handle_prompt(char *prompt, char **envp)
{
		char	*path;
		char	*pwd;
		char **cmd;
		char **split_path;
		int pid;

		pwd = NULL;
		if (prompt == NULL || prompt[0] == '\0')
			return;
		pid = fork();

		if (pid != 0)
		{
			waitpid(pid, NULL, 0);
			return ;
		}
		path = check_envp(envp);
		cmd = ft_split(prompt, ' ');
		split_path = ft_split_path(path, cmd[0]);
		path = check_cmdpath(split_path);
		if (!path)
		{
			pwd = getcwd(pwd, 4096);
			cmd = ft_split(prompt, ' ');
			split_path = ft_split_path(pwd, cmd[0]);
			if (!(pwd = check_cmdpath(split_path)))
			{
				printf("minishell: %s: command not found\n", cmd[0]);
				exit(0);
			}
			execve(pwd, cmd, envp);
		}

		else
			execve(path, cmd, envp);

}
int	main(int ac, char *av[], char **envp)
{
	char	*prompt;
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
		prompt = readline(PROGRAM_NAME);
		handle_prompt(prompt, envp);
	}

}
