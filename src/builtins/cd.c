/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:58:58 by jsubel            #+#    #+#             */
/*   Updated: 2022/05/19 09:55:01 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_cd(char **args, t_env **env)
{
	char	*pwd_old;
	char	*pwd_new;

	pwd_old = NULL;
	pwd_new = NULL;
	pwd_old = getcwd(pwd_old, MAX_DIR);
	if (!pwd_old)
		return (0);
	if (chdir(args[1]) == 0)
	{
		pwd_new = getcwd(pwd_new, MAX_DIR);
		ft_change_pwd(pwd_old, pwd_new, env);
	}
}

void	ft_change_pwd(char *pwd_old, char *pwd_new, t_env **env)
{
	t_env *old;
	t_env *new;

	old = ft_find_element(*env, "OLDPWD");
	new = ft_find_element(*env, "PWD");
	if (old)
		free(old);
	ft_lstadd_back(env, old);
}

t_env	*ft_find_element(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->var))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}