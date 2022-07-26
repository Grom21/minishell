#include "minishell.h"

void	ft_save_envp_on_list(t_list **list, char *env)
{
	int	x;
	int	y;

	x = 0;
	while (env[x] != '\0' && env[x] != '=')
	{
		(*list)->key[x] = env[x];
		x++;
	}
	(*list)->key[x] = '\0';
	if (env[x] == '=')
		x++;
	y = 0;
	while (env[x] != '\0')
	{
		(*list)->value[y] = env[x];
		x++;
		y++;
	}
	(*list)->value[y] = '\0';
}

static t_list	*ft_create_elem(char *env, int count_key, int count_val)
{
	t_list	*list;

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

static void	ft_create_next(t_list **list, char *env, t_list **lastlist)
{
	int		count_key;
	int		count_val;

	count_key = ft_strlen_key(env);
	count_val = ft_strlen_value(env);
	if (!(*lastlist))
	{
		*list = ft_create_elem(env, count_key, count_val);
		if (!list)
		{
			ft_free_memory_envp_list(list);
			exit (1);
		}
	}
	else
	{
		while ((*lastlist)->next)
			(*lastlist) = (*lastlist)->next;
		(*lastlist)->next = ft_create_elem(env, count_key, count_val);
		if (!(*lastlist)->next)
		{
			ft_free_memory_envp_list(list);
			exit (1);
		}
	}
}

void	ft_init_envp_list(t_list **envp_list, char **env)
{
	int		x;
	char	**matrix;
	int		i;
	t_list	*lastlist;

	*envp_list = NULL;
	x = 0;
	while (env[x])
	{
		matrix = ft_split(env[x], '=');
		if (!matrix)
			exit (1);
		lastlist = *envp_list;
		ft_create_next(envp_list, env[x], &lastlist);
		i = 0;
		while (matrix[i])
			i++;
		ft_free_memory_split(matrix, i);
		x++;
	}
}
