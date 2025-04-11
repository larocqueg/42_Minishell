valgrind --suppressions=$HOME/readline.supp --track-fds=yes --leak-check=full --track-origins=yes  --show-leak-kinds=all ./minishell
