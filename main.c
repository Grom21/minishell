#include "minishell.h"

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
		signal(SIGQUIT, SIG_IGN);
		ft_readline(&mini);
		ft_lexer(&mini.lexer, mini.input);
		if((g_last_exit = ft_parser(&mini)) == 0)
			ft_execution(&mini);
		free (mini.input);
		mini.input = NULL;
		ft_free_memory_lexer_list(&mini.lexer);
	}
	return (0);
}
