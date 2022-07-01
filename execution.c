#include "minishell.h"

static int	ft_found_funct(t_lexer *lexer, int i, t_shell *mini)
{
	if (i == 0)
		return (ft_echo(lexer, mini->envp_list));
	else if (i == 2)
		return (ft_pwd());
	else if (i == 3)
		return (ft_export(lexer, mini->envp_list));
	else if (i == 4)
		return (ft_unset(lexer, mini->envp_list));
	else if (i == 5)
		return (ft_env(mini->envp_list));
	else if (i == 6)
		ft_exit(mini);
	return (0);
}

static t_lexer	*ft_next_command(t_lexer *copy)
{
	while (copy && copy->chank[0] != '|')
		copy = copy->next;
	return (copy);
}

static void	ft_command_not_found(t_lexer *copy, t_list *envp_list)
{
	ft_print_parser_error(&copy, COMMAND_NOT_FOUND);
	return ;
}

int	ft_execution(t_shell *mini)
{
	t_lexer	*copy;
	int		i;
	int		result;

	copy = mini->lexer;
	while (copy)
	{
		i = -1;
		while (++i < 11)
		{
			if (ft_strcmp(copy->chank, mini->comand[i]) == 0)
			{
				if ((result = ft_found_funct(copy, i, mini)) != 0)
					return (result);	//rly return???
				break ;
			}
		}
		if (i == 11 && copy->chank[0] != '\0')
			ft_command_not_found(copy, mini->envp_list);
		copy = ft_next_command(copy);	// "|"!
	}
	return (0);
}
