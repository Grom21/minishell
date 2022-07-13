#include "minishell.h"

static int	save_delimeter(t_lexer **new, t_lexer **old, t_list *envp_list)
{
	t_lexer	*new_copy;

	new_copy = *new;
	while (new_copy->next)
		new_copy = new_copy->next;
	ft_parser_save(new_copy, *old, envp_list);		//return!
	*old = (*old)->next;
	if (*old && (*old)->chank[0] == ' ')
		*old = (*old)->next;
	return (0);
}

static int	save_arg(t_lexer **new, t_lexer **old, t_list *envp_list)
{
	t_lexer	*new_copy;

	new_copy = *new;
	while (new_copy->next)
		new_copy = new_copy->next;
	while (*old && (*old)->chank[0] != '|' && (*old)->chank[0] != '<' \
	&& (*old)->chank[0] != '>')
	{
		ft_parser_save(new_copy, *old, envp_list);		//return!
		*old = (*old)->next;
	}
	return (0);
}

static int	save_command(t_lexer **new, t_lexer **old, t_list *envp_list)
{
	t_lexer	*new_copy;

	new_copy = *new;
	while (new_copy->next)
		new_copy = new_copy->next;
	while (*old && (*old)->chank[0] != ' ' && (*old)->chank[0] != '|' \
	&& (*old)->chank[0] != '<' && (*old)->chank[0] != '>')
	{
		ft_parser_save(new_copy, *old, envp_list);		//return!
		*old = (*old)->next;
	}
	if (*old && (*old)->chank[0] == ' ')
		*old = (*old)->next;
	if (*old && (*old)->chank[0] != ' ' && (*old)->chank[0] != '|' \
	&& (*old)->chank[0] != '<' && (*old)->chank[0] != '>')
	{
		ft_parser_create(new);		//protect malloc!
		save_arg(new, old, envp_list);
	}
	return (0);
}

static int	ft_open_quotes(t_shell *mini)
{
	t_lexer	*old;
	t_lexer	*new;

	new = NULL;
	old = mini->lexer;
	while (old)
	{
		if (old && old->chank[0] != ' ' && old->chank[0] != '|' \
		&& old->chank[0] != '<' && old->chank[0] != '>')
		{
			ft_parser_create(&new);		//protect malloc!
			save_command(&new, &old, mini->envp_list);
		}
		if (old && (old->chank[0] == '|' || old->chank[0] == '<' \
		|| old->chank[0] == '>'))
		{
			ft_parser_create(&new);		//protect malloc!
			save_delimeter(&new, &old, mini->envp_list);
		}
		if (old && old->chank[0] == ' ')
			old = old->next;
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
