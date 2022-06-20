all: 
	gcc -g -lreadline *.c -o minishell

clean: 
	rm -f minishell

