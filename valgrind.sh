valgrind --suppressions=$HOME/readline.supp --track-fds=yes --trace-children=yes --leak-check=full  --track-origins=yes  --show-leak-kinds=all ./minishell
