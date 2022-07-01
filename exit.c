#include "minishell.h"

void	ft_exit_signal(t_shell *mini)
{
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	if (mini->input)
		free (mini->input);
	write (1, "\033[0F", 4);
	write(1, "minishell$ exit\n", 16);
	ft_default_term(mini);
	exit (EXIT_SUCCESS);
}

static void	ft_exam_exit(t_lexer *copy)
{
	int	i;

	i = 0;
	while (copy->chank[i] && copy->chank[i] != ' ')
	{
		if ((ft_isdigit(copy->chank[i]) == 0 && i != 0) \
		|| (i == 0 && copy->chank[i] != '-' && copy->chank[i] != '+'))
		{
			write(1, "minishell: exit: ", 17);
			i = 0;
			while (copy->chank[i] != '\0' && copy->chank[i] != ' ')
				write(1, &copy->chank[i++], 1);
			write (1, ": numeric argument required\n", 28);
			exit (255);
		}
		i++;
	}
	if (copy->chank[i] != '\0')
	{
		write(1, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	else
		exit (ft_atoi(copy->chank));
}

void	ft_exit(t_shell *mini)
{
	t_lexer *copy;

	copy = mini->lexer->next;
	write (1, "exit\n", 5);
	if (copy)
	{
		ft_exam_exit(copy);
		return ;
	}
	ft_free_memory_lexer_list(&mini->lexer);
	ft_free_memory_envp_list(&mini->envp_list);
	ft_free_memory_matrix(mini->envp);
	ft_free_memory_matrix(mini->comand);
	if (mini->input)
		free (mini->input);
	ft_default_term(mini);
	exit (EXIT_SUCCESS);
}
