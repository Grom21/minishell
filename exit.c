#include "minishell.h"

void	ft_exit_signal(t_shell *mini)
{
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	write (1, "\033[0F", 4);
	write(1, "minishell$ exit\n", 16);
	ft_default_term(mini);
	exit (EXIT_SUCCESS);
}
