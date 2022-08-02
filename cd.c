/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbilli <sbilli@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:01:13 by etisha            #+#    #+#             */
/*   Updated: 2022/07/31 20:26:32 by sbilli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_home(t_list *envp_list)
{
	t_list	*home;
	char	*old_pwd;

	home = ft_found_in_envp(envp_list, "HOME");
	if (!home)
		return (ft_cd_error(HOME_NOT_SET, ""));
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (chdir(home->value) != 0)
	{
		free (old_pwd);
		if (errno == EACCES)
			return (ft_cd_error(PERMISSION_DENIED, home->value));
		else
			return (ft_cd_error(NO_SUCH_FILE_OR_DIR, home->value));
	}
	if (ft_update_envp_old_pwd(envp_list, old_pwd) != 0)
		return (ft_free_envp_old_pwd(old_pwd));
	free (old_pwd);
	if (ft_update_envp_pwd(envp_list) != 0)
		return (1);
	return (0);
}

static int	ft_old_pwd(t_list *envp_list)
{
	t_list	*old_pwd;
	char	*pwd;

	old_pwd = ft_found_in_envp(envp_list, "OLDPWD");
	if (!old_pwd)
		return (ft_cd_error(OLDPWD_NOT_SET, ""));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	if (chdir(old_pwd->value) != 0)
	{
		free (pwd);
		if (errno == EACCES)
			return (ft_cd_error(PERMISSION_DENIED, old_pwd->value));
		else
			return (ft_cd_error(NO_SUCH_FILE_OR_DIR, old_pwd->value));
	}
	if (ft_update_envp_old_pwd(envp_list, pwd) != 0)
		return (ft_free_envp_old_pwd(pwd));
	free (pwd);
	if (ft_update_envp_pwd(envp_list) != 0)
		return (1);
	return (0);
}

static int	ft_old_pwd_print(t_list *envp_list)
{
	t_list	*old_pwd;
	char	*pwd;

	old_pwd = ft_found_in_envp(envp_list, "OLDPWD");
	if (!old_pwd)
		return (ft_cd_error(OLDPWD_NOT_SET, ""));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	if (chdir(old_pwd->value) != 0)
	{
		free (pwd);
		if (errno == EACCES)
			return (ft_cd_error(PERMISSION_DENIED, old_pwd->value));
		else
			return (ft_cd_error(NO_SUCH_FILE_OR_DIR, old_pwd->value));
	}
	if (ft_update_envp_old_pwd(envp_list, pwd) != 0)
		return (ft_free_envp_old_pwd(pwd));
	free (pwd);
	if (ft_update_envp_pwd(envp_list) != 0)
		return (1);
	return (ft_pwd());
}

static int	ft_cd_path(t_lexer *lexer, t_list *envp_list)
{
	char	*old_pwd;

	if (ft_strlen(lexer->chank) > 255)
		return (ft_cd_error(FILE_NAME_TOO_LONG, lexer->chank));
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (chdir(lexer->chank) != 0)
	{
		free (old_pwd);
		if (errno == EACCES)
			return (ft_cd_error(PERMISSION_DENIED, lexer->chank));
		else
			return (ft_cd_error(NO_SUCH_FILE_OR_DIR, lexer->chank));
	}
	if (ft_update_envp_old_pwd(envp_list, old_pwd) != 0)
	{
		free (old_pwd);
		return (1);
	}
	free (old_pwd);
	if (ft_update_envp_pwd(envp_list) != 0)
		return (1);
	return (0);
}

int	ft_cd(t_lexer *lexer, t_shell *mini)
{
	t_lexer	*copy;
	int		result;

	copy = lexer->next;
	if (copy && copy->chank[0] == '\0')
		return (0);
	if (!copy || copy->chank[0] == '|' || (copy->chank[0] == '~' && \
	(copy->chank[1] == ' ' || copy->chank[1] == '\0')))
		result = ft_cd_home(mini->envp_list);
	else if (copy && copy->chank[0] == '~' && copy->chank[1] == '-' \
	&& (copy->chank[2] == ' ' || copy->chank[2] == '\0'))
		result = ft_old_pwd(mini->envp_list);
	else if (copy && copy->chank[0] == '-' \
	&& (copy->chank[1] == ' ' || copy->chank[1] == '\0'))
		result = ft_old_pwd_print(mini->envp_list);
	else
		result = ft_cd_path(copy, mini->envp_list);
	return (result);
}
