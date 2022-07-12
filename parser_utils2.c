#include "minishell.h"

static int	ft_single_quotes(t_lexer *new_copy, t_lexer *old_copy, int i)
{
	char	buf[2];
	char	*str;

	buf[1] = '\0';
	while (old_copy->chank[++i] != '\'')
	{
		buf[0] = old_copy->chank[i];
		if ((str = ft_strjoin(new_copy->chank, buf)) == NULL)
			return (-1);
		free (new_copy->chank);
		new_copy->chank = str;
		str = NULL;
	}
	i++;
	return (i);
}

static int	ft_exit_status(t_lexer *new, t_lexer *old, int i)	//need rewrite this!!!
{
	char	*exit_status;
	int		x;

	if (old->chank[i] == '$' && old->chank[i + 1] == '?')
	{
		if ((exit_status = ft_itoa(g_last_exit)) == NULL)
			return (-1);
		x = 0;
		while (exit_status[x])
		{
			if(ft_save_char(new, exit_status[x]) != 0)
			{
				free (exit_status);
				return (-1);
			}
			x++;
		}
		i++;
		i++;
	}
	return (i);
}

static int	ft_word(t_lexer *new, t_lexer *old, int i, t_list *envp)
{
	while (old->chank[i] != '\0')
	{
		if ((i = ft_exit_status(new, old, i)) < 0)
			return (-1);
		if (old->chank[i] == '$' && old->chank[i + 1] == '$')
		{
			if(ft_save_char(new, old->chank[i++]) != 0 \
			|| ft_save_char(new, old->chank[i]) != 0)
				return (-1);
		}
		else if (old->chank[i] == '$' && old->chank[i + 1] != '?')
		{
			if((i = ft_take_envp(new, old, i, envp)) < 0)
				return (-1);
		}
		else
		{
			if(ft_save_char(new, old->chank[i]) != 0)
				return (-1);
		}
		i++;
	}
	return (i);
}

static int	ft_double_quotes(t_lexer *new, t_lexer *old, int i, t_list *envp)
{
	while (old->chank[++i] != '\"')
	{
		if ((i = ft_exit_status(new, old, i)) < 0)
			return (-1);
		else if (old->chank[i] == '$' && old->chank[i + 1] == '$')
		{
			if(ft_save_char(new, old->chank[i++]) != 0 \
			|| ft_save_char(new, old->chank[i]) != 0)
				return (-1);
		}
		else if (old->chank[i] == '$' && old->chank[i + 1] != '?')
		{
			if((i = ft_take_envp(new, old, i, envp)) < 0)
				return (-1);
		}
		else
		{
			if(ft_save_char(new, old->chank[i]) != 0)
				return (-1);
		}
	}
	i++;
	return (i);
}

int	ft_parser_save(t_lexer *new_copy, t_lexer *old_copy, t_list *envp_list)
{
	int	i;

	i = 0;
	while (old_copy->chank[i])
	{
		if (old_copy->chank[i] == '\'')
		{
			if ((i = ft_single_quotes(new_copy, old_copy, i)) < 0)
				return (-1);
		}
		else if (old_copy->chank[i] == '\"')
		{
			if ((i = ft_double_quotes(new_copy, old_copy, i, envp_list)) < 0)
				return (-1);
		}
		else
		{
			if ((i = ft_word(new_copy, old_copy, i, envp_list)) < 0)
				return (-1);
		}
	}
	return (0);
}
