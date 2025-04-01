/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/30 15:35:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

static char	**clone_envp(char **envp)
{
	int	i;
	char **dest;

	i = 0;
	while (envp[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dest[i] = ft_strdup(envp[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	ft_swap(char **s1, char **s2)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static int	ft_strcmp_tochar(const char *s1, const char *s2, char c)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) || s1[i] != c || s2[i] != c)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	print_export(t_shell *sh)
{
	int i;
	int	j;
	char **temp2;

	i = 0;
	temp2 = clone_envp(sh->envp);
	while (temp2[i])
	{
		j = i + 1;
		while (temp2[j])
		{
			if (ft_strcmp_tochar(temp2[i], temp2[j], '=') > 0)
				ft_swap(&temp2[i], &temp2[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (temp2[i])
	{
		printf("declare -x %s\n", temp2[i]);
		free(temp2[i++]);
	}
	free(temp2);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	sh.DEBUG = 0;
	if (argc == 2 && argv[1][0] == '1')
		sh.DEBUG = 1;
	sh.original_stdin = dup(STDIN_FILENO);
	sh.original_stdout = dup(STDOUT_FILENO);
	g_exit_code = 2;
	sh.envp = clone_envp(envp); // dar free em caso de exit ou ctrl + d
	sh.pipe_old = NULL;
	sh.pipe_new = NULL;
	sh.heredoc_count = 0;
	start_cli(&sh);
	return (0);
}

