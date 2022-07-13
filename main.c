#include "minishell.h"

int	g_last_exit = 0;

static void	ft_readline(t_shell *mini)
{
	mini->input = readline("minishell$ ");
	if (!mini->input)
		ft_exit_signal(mini);
	if (mini->input[0] != '\0')
		add_history(mini->input);
}

int	main (int argc, char **argv, char **env)
{
	t_shell	mini;
	int		result_command;

	ft_new_term_settings(&mini);
	ft_init(&mini, env);
	while (1)
	{
		signal(SIGINT, ft_signal);
		// signal(SIGQUIT, SIG_IGN);
		ft_readline(&mini);
		ft_lexer(&mini.lexer, mini.input);

		if(ft_parser(&mini) == 0)
		{
			ft_execution(&mini);
		}

		// test lekser work
		// t_lexer *copy;
		// copy = mini.lexer;
		// while (copy)
		// {
		// 	printf("%s\n", copy->chank);
		// 	copy = copy->next;
		// }


		free (mini.input);
		mini.input = NULL;
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

	// ft_free_memory_envp_list(&mini.envp_list);
	// ft_free_memory_matrix(mini.envp);
	// ft_free_memory_matrix(mini.comand);
	// mini.comand = NULL;
	// mini.envp = NULL;
	// mini.envp_list = NULL;
	// mini.input = NULL;
	// mini.lexer = NULL;


	return (0);
}
