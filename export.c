#include "minishell.h"

static t_list	*ft_create_elem(char *env, int count_key, int count_val)
{
	t_list	*list;
	int		x;
	int		y;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->key = NULL;
	list->value = NULL;
	list->key = (char *)malloc(sizeof(char) * (count_key + 1));
	list->value = (char *)malloc(sizeof(char) * (count_val + 1));
	if (!list->key || !list->value)
		return (NULL);
	ft_save_envp_on_list(&list, env);
	list->next = NULL;
	return (list);
}

static int	ft_create_next(t_list **list, char *env, t_list **lastlist)
{
	int		count_key;
	int		count_val;

	count_key = ft_strlen_key(env);
	count_val = ft_strlen_value(env);
	if (!(*list))
	{
		*list = ft_create_elem(env, count_key, count_val);
		if (!(*list))
		{
			ft_free_memory_envp_list(list);
			return (1);
		}
	}
	else
	{
		(*lastlist)->next = ft_create_elem(env, count_key, count_val);
		if (!(*lastlist)->next)
		{
			ft_free_memory_envp_list(&(*lastlist)->next);
			return (1);
		}
	}
	return (0);
}

static int	ft_change_envp(t_list *copy_envp, char *str, char *key)
{
	int		len;
	char	*new_value;
	int		i;

	len = ft_strlen_value(str);
	new_value = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return (1);
	len = ft_strlen_key(str) + 1;
	i = 0;
	while (str[len])
	{
		new_value[i] = str[len];
		len++;
		i++;
	}
	new_value[i] = '\0';
	free (copy_envp->value);
	free (key);
	copy_envp->value = new_value;
	return (0);
}

int	ft_export_run(char *str, t_list *envp_list, int len)
{
	t_list	*last_envp;
	t_list	*copy_envp;
	char	*key;

	copy_envp = envp_list;
	last_envp = envp_list;
	while (last_envp->next)
		last_envp = last_envp->next;
	if (ft_strchr(str, '=') == NULL)
		return (0);
	len = ft_strlen_key(str);
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (1);
	ft_strlcpy(key, str, len + 1);
	if (ft_exam_export_key(str, key) != 0)
		return (1);
	while (copy_envp)
	{
		if (ft_strcmp(key, copy_envp->key) == 0)
			return (ft_change_envp(copy_envp, str, key));
		copy_envp = copy_envp->next;
	}
	free (key);
	return (ft_create_next(&envp_list, str, &last_envp));
}

int	ft_export(t_lexer *lexer, t_list *envp_list)
{
	t_lexer	*lexer_copy;
	int		result;
	int		i;
	char	**matrix;

	result = 0;
	lexer_copy = lexer->next;
	if (ft_exam_void(lexer, envp_list) != 0)
		return (0);
	if (ft_strchr(lexer_copy->chank, '=') == NULL)
		return (0);
	matrix = ft_split(lexer_copy->chank, ' ');
	if (!matrix)
		return (1);
	i = 0;
	while (matrix[i])
	{
		if (ft_export_run(matrix[i], envp_list, 0) != 0)
			result = 1;
		i++;
	}
	ft_free_memory_matrix(matrix);
	return (result);
}
