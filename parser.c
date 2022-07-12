#include "minishell.h"

static int	ft_save_info(t_lexer **new, t_lexer **old_copy, t_list *envp_list)
{
	t_lexer	*new_copy;
	char	*buffer;

	new_copy = *new;
	while (new_copy->next)
		new_copy = new_copy->next;
	// if (ft_strcmp(new_copy->chank, "-n") == 0)	// del! -n in one chank!
	// {
	// 	ft_parser_create(new);		//protect malloc!
	// 	new_copy = new_copy->next;
	// }
	while (*old_copy && (*old_copy)->chank[0] != '|')
	{
		ft_parser_save(new_copy, *old_copy, envp_list);
		*old_copy = (*old_copy)->next;
	}
	if (*old_copy && (*old_copy)->chank[0] == '|')
	{
		ft_parser_create(new);		//protect malloc!
		new_copy = new_copy->next;
		return (ft_parser_save(new_copy, *old_copy, envp_list));
	}
	return (0);
}

static int	save_command(t_lexer **new, t_lexer **old_copy, t_list *envp_list)
{
	t_lexer	*new_copy;
	char	*buffer;

	new_copy = *new;
	while (new_copy->next)
		new_copy = new_copy->next;
	while (*old_copy && (*old_copy)->chank[0] != ' ' \
	&& (*old_copy)->chank[0] != '|')
	{
		ft_parser_save(new_copy, *old_copy, envp_list);		//return!
		*old_copy = (*old_copy)->next;
	}
	if (*old_copy && (*old_copy)->chank[0] == ' ')
		*old_copy = (*old_copy)->next;
	if (*old_copy && (*old_copy)->chank[0] != '|')
	{
		ft_parser_create(new);		//protect malloc!
		new_copy = new_copy->next;
		ft_parser_save(new_copy, *old_copy, envp_list);		//return!
		*old_copy = (*old_copy)->next;
		// if (*old_copy && (*old_copy)->chank[0] == ' ' \  // del! -n in one chank!
		// && ft_strcmp(new_copy->chank, "-n") == 0)
		// 	*old_copy = (*old_copy)->next;
	}
	return (0);
}

static int	ft_open_quotes(t_shell *mini)
{
	t_lexer	*old_copy;
	t_lexer	*new;

	new = NULL;
	old_copy = mini->lexer;
	while (old_copy)
	{
		ft_parser_create(&new);		//protect malloc!
		save_command(&new, &old_copy, mini->envp_list);
		if (old_copy)
			ft_save_info(&new, &old_copy, mini->envp_list);
		if (old_copy && old_copy->chank[0] == '|')
			old_copy = old_copy->next;
		if (old_copy && old_copy->chank[0] == ' ')
			old_copy = old_copy->next;
	}
	ft_free_memory_lexer_list(&mini->lexer);
	mini->lexer = new;
	return (0);
}

int	ft_parser(t_shell *mini)
{
	int	result;

	if ((result = ft_exam_pipe_first_last_double(mini)) != 0)
		return (result);
	if ((result = ft_exam_syntax_quotes(mini)) != 0)
		return (result);
	if ((result = ft_exam_double_redirect(mini)) != 0)
		return (result);
	if ((result = ft_open_quotes(mini)) !=0)
		return (result);
	if (mini->lexer->chank[0] == '\0')
		return (1);
	return (0);
}
