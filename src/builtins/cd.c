/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:58:58 by jsubel            #+#    #+#             */
/*   Updated: 2022/06/08 09:29:05 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void		ft_change_env_pwd(char *pwd_old, char *pwd_new, t_env *env);
static int		ft_cd_no_args(t_shell *shell, char *pwd_old, t_env *env);
static int		ft_cd_last_directory(t_shell *shell, char *pwd_old, t_env *env);

/**
 * @brief recode of change directory (cd) builtin
 * @param pwd_old string to save working directory before changing
 * @param pwd_new string to save working directory after changing
 */
int	ft_cd(t_shell *shell, t_args *args, t_env *env)
{
	char	*pwd_old;
	char	*pwd_new;

	pwd_old = NULL;
	pwd_new = NULL;
	pwd_old = getcwd(pwd_old, MAXPATHLEN);
	if (args->next->next)
		return (ft_error_msg(shell, ERR_EXIT_COUNT, ERRNO_EXIT_COUNT));
	if (args->next == NULL)
		return (ft_cd_no_args(shell, pwd_old, env));
	if (!pwd_old)
		perror(ERR_PAR_DIR);
	if (!pwd_old)
		return (ERRNO_PAR_DIR);
	if (ft_strncmp(args->next->arg, "-", 1) == 0)
		return (ft_cd_last_directory(shell, pwd_old, env));
	if (chdir(args->next->arg) != 0)
		ft_error_msg(shell, args->next->arg, 0);
	else
	{
		pwd_new = getcwd(pwd_new, MAXPATHLEN);
		ft_change_env_pwd(pwd_old, pwd_new, shell->env);
	}
	free(pwd_old);
	free(pwd_new);
	return (0);
}

//			excel: 430/431

/**
 * @brief helper function to swap around the OLDPWD and PWD variables in env
 * @param old env element holding the old pwd
 * @param new env element holding the new pwd
 * @param tmp temp string storage
 */
static void	ft_change_env_pwd(char *pwd_old, char *pwd_new, t_env *env)
{
	t_env	*old;
	t_env	*new;
	char	*tmp;

	old = ft_find_element(env, "OLDPWD");
	new = ft_find_element(env, "PWD");
	if (!new)
		return ;
	if (old)
	{
		free(old->var);
		pwd_old = ft_strjoin("OLDPWD=", pwd_old);
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
	free(pwd_old);
	free(pwd_new);
}

/** @brief find a certain element within env */
t_env	*ft_find_element(t_env *env, char *str)
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

/** @brief if cd gets called with no arguments, use this */
static int	ft_cd_no_args(t_shell *shell, char *pwd_old, t_env *env)
{
	t_env	*home;
	char	*pwd_home;

	if (!pwd_old)
		pwd_old = ft_substr(ft_find_element(shell->env, "PWD")->var, \
			5, ft_strlen(ft_find_element(shell->env, "PWD")->var) - 5);
	home = ft_find_element(shell->env, "HOME");
	if (!home)
	{
		ft_error_msg(shell, ERR_HOME_UNSET, ERRNO_HOME_UNSET);
		return (ERRNO_HOME_UNSET);
	}
	pwd_home = ft_substr(home->var, 5, ft_strlen(home->var) - 5);
	if (chdir(pwd_home) != 0)
		ft_error_msg(shell, "cd: ", 0);
	ft_change_env_pwd(pwd_old, pwd_home, env);
	free(pwd_home);
	free(pwd_old);
	return (0);
}

static int	ft_cd_last_directory(t_shell *shell, char *pwd_old, t_env *env)
{
	t_env	*last_dir;
	char	*pwd_last;

	if (!pwd_old)
		pwd_old = ft_substr(ft_find_element(shell->env, "PWD")->var, \
			5, ft_strlen(ft_find_element(shell->env, "PWD")->var) - 5);
	last_dir = ft_find_element(shell->env, "OLDPWD");
	if (!last_dir)
	{
		ft_error_msg(shell, ERR_OLDPWD_UNSET, ERRNO_OLDPWD_UNSET);
		return (ERRNO_OLDPWD_UNSET);
	}
	pwd_last = ft_substr(last_dir->var, 7, ft_strlen(last_dir->var) - 7);
	if (chdir(pwd_last) != 0)
		ft_error_msg(shell, "cd: ", 0);
	ft_change_env_pwd(pwd_old, pwd_last, env);
	free(pwd_last);
	free(pwd_old);
	return (0);
}
