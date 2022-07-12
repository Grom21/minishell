#include "minishell.h"

t_list *ft_found_in_envp(t_list *envp_list, char *key)
{
	t_list	*copy_envp;

	copy_envp = envp_list;
	while (copy_envp)
	{
		if (ft_strcmp(copy_envp->key, key) == 0)
			break ;
		copy_envp = copy_envp->next;
	}
	return (copy_envp);
}

int	ft_update_envp_old_pwd(t_list *envp_list, char *old_pwd)
{
	char	*buf;

	if ((buf = ft_strjoin("OLDPWD=", old_pwd)) == NULL)
		return (1);
	if (ft_export_run(buf, envp_list) != 0)
	{
		free (buf);
		return (1);
	}
	free (buf);
	return (0);
}

int	ft_update_envp_pwd(t_list *envp_list)
{
	char	*buf;
	char	*new_pwd;

	if ((new_pwd = getcwd(NULL, 0)) == NULL)
		return (1);
	if ((buf = ft_strjoin("PWD=", new_pwd)) == NULL)
	{
		free (new_pwd);
		return (1);
	}
	if (ft_export_run(buf, envp_list) != 0)
	{
		free (buf);
		free (new_pwd);
		return (1);
	}
	free (buf);
	free (new_pwd);
	return (0);
}
