/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:03:32 by etisha            #+#    #+#             */
/*   Updated: 2022/07/27 01:03:33 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_crazy_save(char *comand, char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		comand[i] = word[i];
		i++;
	}
	comand[i] = '\0';
}

static char	**ft_hardcode(char **comand, int i)
{
	comand = (char **)malloc(sizeof(char *) * 8);
	if (!comand)
		return (NULL);
	while (i < 7)
	{
		comand[i] = (char *)malloc(sizeof(char) * 7);
		if (!comand[i])
		{
			ft_free_memory_split(comand, i);
			return (NULL);
		}
		i++;
	}
	ft_crazy_save(comand[0], "echo");
	ft_crazy_save(comand[1], "cd");
	ft_crazy_save(comand[2], "pwd");
	ft_crazy_save(comand[3], "export");
	ft_crazy_save(comand[4], "unset");
	ft_crazy_save(comand[5], "env");
	ft_crazy_save(comand[6], "exit");
	comand[7] = NULL;
	return (comand);
}

static void	ft_upgrade_envp_list_shlvl(t_list **envp_list)
{
	t_list	*copy;
	int		shlvl;

	copy = *envp_list;
	while (copy)
	{
		if (ft_strcmp(copy->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(copy->value) + 1;
			free (copy->value);
			copy->value = ft_itoa(shlvl);
			if (!copy->value)
			{
				ft_free_memory_envp_list(envp_list);
				exit (1);
			}
		}
		copy = copy->next;
	}
}

void	ft_init(t_shell	*mini, char **env)
{
	ft_init_envp_list(&mini->envp_list, env);
	ft_upgrade_envp_list_shlvl(&mini->envp_list);
	mini->envp = ft_new_envp(&mini->envp_list);
	if (!mini->envp)
	{
		ft_free_memory_envp_list(&mini->envp_list);
		exit (1);
	}
	mini->comand = ft_hardcode(mini->comand, 0);
	if (!mini->comand)
	{
		ft_free_memory_envp_list(&mini->envp_list);
		ft_free_memory_matrix(mini->envp);
		exit (1);
	}
	mini->lexer = NULL;
}
