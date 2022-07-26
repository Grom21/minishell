#include "minishell.h"

static void	ft_save(char **envp, t_list **envp_list, int size)
{
	t_list	*copy;
	int		x;
	int		y;
	int		z;

	copy = *envp_list;
	x = 0;
	while (copy)
	{
		y = 0;
		z = 0;
		while (copy->key[z])
			envp[x][y++] = copy->key[z++];
		envp[x][y++] = '=';
		z = 0;
		while (copy->value[z])
			envp[x][y++] = copy->value[z++];
		envp[x++][y] = '\0';
		copy = copy->next;
	}
	envp[x] = NULL;
}

static char	**ft_create_matrix(char	**envp, t_list **envp_list)
{
	int		i;
	int		size;
	t_list	*copy;

	copy = *envp_list;
	i = 0;
	while (copy)
	{
		size = 0;
		size = ft_strlen(copy->key) + ft_strlen(copy->value) + 1;
		envp[i] = (char *)malloc(sizeof(char) * (size + 1));
		if (!envp[i])
		{
			ft_free_memory_split(envp, i);
			return (NULL);
		}
		copy = copy->next;
		i++;
	}
	return (envp);
}

char	**ft_new_envp(t_list **envp_list)
{
	char	**envp;
	int		size;
	t_list	*copy;
	int		i;

	copy = *envp_list;
	size = 0;
	while (copy)
	{
		copy = copy->next;
		size++;
	}
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	envp = ft_create_matrix(envp, envp_list);
	ft_save(envp, envp_list, size);
	return (envp);
}
