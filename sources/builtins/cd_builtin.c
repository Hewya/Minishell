/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:47:15 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/27 12:07:41 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_wds(t_data *data, char *wd)
{
	if (data->working_dir)
		set_env_var(data, "OLDPWD", data->working_dir);
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
		free_ptr(data->old_working_dir);
	data->old_working_dir = ft_strdup(data->working_dir);
	if (data->working_dir)
		free_ptr(data->working_dir);
	data->working_dir = ft_strdup(wd);
	free_ptr(wd);
}

static	bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (false);
}

static bool	change_dir(t_data *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0')
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		if (data->old_working_dir == NULL)
			return (pwd_builtin());
		return (!change_dir(data, data->old_working_dir));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	return (!change_dir(data, args[1]));
}
