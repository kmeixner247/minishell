/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:58:58 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/23 15:43:53 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void		ft_change_env_pwd(char *pwd_old, char *pwd_new, t_env *env);
static t_env	*ft_find_element(t_env *env, char *str);
static int		ft_cd_no_args(char *pwd_old, t_env *env);

int	ft_cd(t_args *args, t_env *env)
{
	char	*pwd_old;
	char	*pwd_new;
	t_env	*home;

	pwd_old = NULL;
	pwd_new = NULL;
	pwd_old = getcwd(pwd_old, MAXPATHLEN);
	if (!pwd_old)
		return (0);
	if (args->next == NULL)
		return (ft_cd_no_args(pwd_old, env));
	if (chdir(args->next->arg) != 0)
		ft_error_msg(args->next->arg);
	else
	{
		pwd_new = getcwd(pwd_new, MAXPATHLEN);
		ft_change_env_pwd(pwd_old, pwd_new, env);
	}
	return (1);
}

static void	ft_change_env_pwd(char *pwd_old, char *pwd_new, t_env *env)
{
	t_env	*old;
	t_env	*new;
	char	*tmp;

	old = ft_find_element(env, "OLDPWD");
	new = ft_find_element(env, "PWD");
	if (old)
	{
		free(old->var);
		pwd_old = ft_strjoin("OLDPWD", pwd_old);
		old->var = ft_strdup(pwd_old);
	}
	else
	{
		tmp = ft_strjoin("OLDPWD=", pwd_old);
		env_addback(&env, new_env(tmp));
		free(tmp);
	}
	free(new->var);
	pwd_new = ft_strjoin("PWD=", pwd_new);
	new->var = ft_strdup(pwd_new);
}

static t_env	*ft_find_element(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var, ft_strlen(str)))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static int	ft_cd_no_args(char *pwd_old, t_env *env)
{
	t_env	*home;
	char	*pwd_home;

	home = ft_find_element(env, "HOME");
	pwd_home = ft_substr(home->var, 5, ft_strlen(home->var) - 5);
	if (chdir(pwd_home) != 0)
		ft_error_msg("cd: ");
	ft_change_env_pwd(pwd_old, pwd_home, env);
	return (1);
}
