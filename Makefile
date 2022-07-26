all:
	gcc -g *.c -o minishell -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

clean:
	rm -f minishell
# -Wall -Wextra -Werror
# -fsanitize=address
