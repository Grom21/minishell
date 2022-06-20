#include "minishell.h"

int	main (int argc, char **argv, char **env)
{
	t_shell	mini;

	ft_init(&mini, env);
	while (1)
	{
		// write(1, "minishell$ ", 11);
		// mini.input = get_next_line(0);
		mini.input = readline("minishell$ ");
		ft_lexer(&mini.lexer, mini.input);

		ft_parser(&mini);
		



		// test lekser work
		// t_lexer *copy;
		// copy = mini.lexer;
		// while (copy)
		// {
		// 	printf("%s\n", copy->chank);
		// 	copy = copy->next;
		// }


		free (mini.input);
		ft_free_memory_lexer_list(&mini.lexer);
	}



	// test envp:
	// int i = 0;
	// t_list *copy;
	// copy = mini.envp_list;
	// while (mini.envp[i] && env[i] && copy)
	// {
	// 	printf("orig: %s\n", env[i]);
	// 	printf("list: %s=%s\n", copy->key, copy->value);
	// 	copy = copy->next;
	// 	printf("copy: %s\n", mini.envp[i]);
	// 	i++;
	// }

	ft_free_memory_envp_list(&mini.envp_list);
	ft_free_memory_matrix(mini.envp);
	ft_free_memory_matrix(mini.comand);
	mini.comand = NULL;
	mini.envp = NULL;
	mini.envp_list = NULL;
	mini.input = NULL;
	mini.lexer = NULL;


	return (0);
}
