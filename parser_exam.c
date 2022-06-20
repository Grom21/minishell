#include "minishell.h"

int	ft_exam_backslash(t_shell *mini)
{
	t_lexer *copy;

	copy = mini->lexer;
	while (copy->next)
		copy = copy->next;
	if(ft_strcmp(copy->chank, "\\") == 0)
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
		return (SYNTAX_ERROR);
	}
	return (0);
}

static t_lexer	*ft_exam_double_delimiter(t_lexer *copy, t_shell *mini)
{
	t_lexer *nextlist;

	while (copy->next)
	{
		if (copy->chank[0] == ';' || copy->chank[0] == '|')
		{
			nextlist = copy->next;
			if (nextlist->chank[0] == ' ')
				nextlist = nextlist->next;
			if (nextlist->chank[0] == '|' || nextlist->chank[0] == ';')
			{
				ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
				return (NULL);
			}
		}
		copy = copy->next;
	}
	return (copy);
}

int	ft_exam_pipe_first_last_double(t_shell *mini)
{
	t_lexer	*copy;
	t_lexer *nextlist;

	copy = mini->lexer;
	if (ft_strcmp(copy->chank, "|") == 0)
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_PIPE_ERROR);
		return (SYNTAX_PIPE_ERROR);
	}
	copy = ft_exam_double_delimiter(copy, mini);
	if (!copy)
		return (SYNTAX_ERROR);
	if (ft_strcmp(copy->chank, "|") == 0)
	{
		ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
		return (SYNTAX_ERROR);
	}
	return (0);
}

int	ft_exam_syntax_quotes(t_shell *mini)
{
	t_lexer	*copy;
	char	*chank;
	int		len;

	copy = mini->lexer;
	while (copy)
	{
		chank = copy->chank;
		len = ft_strlen(chank);
		if ((chank[0] == '\'' && len == 1) || (chank[0] == '\"' && len == 1))
		{
			ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
			return (SYNTAX_ERROR);
		}
		if ((chank[0] == '\'' && chank[len - 1] != '\'') \
		|| (chank[0] == '\"' && chank[len - 1] != '\"'))
		{
			ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
			return (SYNTAX_ERROR);
		}
		copy = copy->next;
	}
	return (0);
}

int	ft_exam_double_redirect(t_shell *mini)
{
	t_lexer	*copy;
	t_lexer *nextlist;

	copy = mini->lexer;
	while (copy->next)
	{
		if ((copy->chank[0] == '<') || (copy->chank[0] == '>'))
		{
			nextlist = copy->next;
			if (nextlist->chank[0] == ' ')
				nextlist = nextlist->next;
			if (nextlist->chank[0] == '<' || nextlist->chank[0] == '>')
			{
				ft_print_parser_error(&mini->lexer, SYNTAX_ERROR);
				return (SYNTAX_ERROR);
			}
		}
		copy = copy->next;
	}
	return (0);
}
