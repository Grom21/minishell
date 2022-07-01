#include "minishell.h"

static int	ft_exam_unset_void(t_lexer *copy_lexer)
{
	if (!copy_lexer || copy_lexer->chank[0] == '|')
		return (1);
	return (0);
}

static int	ft_exam_unset_key(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) != 1)
		return (ft_print_unset_error(str));
	i = 1;
	while (str[i])
	{
		if ((ft_isdigit(str[i]) == 0) && (ft_isalpha(str[i]) == 0))
			return (ft_print_unset_error(str));
		i++;
	}
	return (0);
}

static int	ft_delit_envp(t_list *copy_envp, t_list *envp_list)
{
	t_list	*previous;

	previous = envp_list;
	while (previous->next != copy_envp)
		previous = previous->next;
	previous->next = copy_envp->next;
	if (copy_envp->key)
		free (copy_envp->key);
	if (copy_envp->value)
		free (copy_envp->value);
	free(copy_envp);
	return (0);
}

static int	ft_unset_run(char *str, t_list *envp_list)
{
	t_list	*copy_envp;

	copy_envp = envp_list;
	if (ft_strchr(str, '=') != NULL)
		return (ft_print_unset_error(str));
	if (ft_exam_unset_key(str) != 0)
		return (1);
	while (copy_envp)
	{
		if (ft_strcmp(str, copy_envp->key) == 0)
			return (ft_delit_envp(copy_envp, envp_list));
		copy_envp = copy_envp->next;
	}
	return (0);
}

int	ft_unset(t_lexer *lexer, t_list *envp_list)
{
	int		i;
	int		result;
	t_lexer	*copy_lexer;
	char	**matrix;

	result = 0;
	copy_lexer = lexer->next;
	if (ft_exam_unset_void(copy_lexer) != 0)
		return (0);
	matrix = ft_split(copy_lexer->chank, ' ');
	if (!matrix)
		return (1);
	i = 0;
	while (matrix[i])
	{
		if (ft_unset_run(matrix[i], envp_list) != 0)
			result = 1;
		i++;
	}
	ft_free_memory_matrix(matrix);
	return (result);
}
