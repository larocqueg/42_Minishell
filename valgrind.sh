
valgrind --suppressions=$HOME/readline.supp --track-fds=yes --leak-check=full --trace-children=yes --track-origins=yes  --show-leak-kinds=all ./minishell
