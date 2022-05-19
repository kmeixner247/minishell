/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:58:58 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/19 15:59:45 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ft_change_pwd(char *pwd_old, char *pwd_new, t_env *env);
static t_env	*ft_find_element(t_env *env, char *str);

int	ft_cd(t_args *args, t_env *env)
{
	char	*pwd_old;
	char	*pwd_new;

	pwd_old = NULL;
	pwd_new = NULL;
	pwd_old = getcwd(pwd_old, 1000);
	if (!pwd_old)
		return (0);
	if (chdir(args->next->arg) == 0)
	{
		pwd_new = getcwd(pwd_new, 1000);
		ft_change_pwd(pwd_old, pwd_new, env);
	}
	return (1);
}

static void	ft_change_pwd(char *pwd_old, char *pwd_new, t_env *env)
{
	t_env	*old;
	t_env	*new;
	char	*tmp;
	
	old = ft_find_element(env, "OLDPWD");
	new = ft_find_element(env, "PWD");
	if (old)
	{
		free(old->var);
		old->var = ft_strdup(new->var);
	}
	else
	{
		env_addback(env, new_env(tmp));
		free(tmp);
	}
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