/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:39:03 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 23:43:16 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	length_env(char **env)
{
	int			i;
	struct stat	cmd;

	i = 0;
	while (env[i])
		i++;
	return (i);
}*/
int	is_directory(char *dir)
{
	struct stat cmd;

	ft_memset(&cmd, 0, sizeof(cmd));
	stat(dir, &cmd);
	return (S_ISDIR(cmd.st_mode));
}

bool	check_builtins(char *cmd)
{
	if ((ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "echo") == 0)
		|| (ft_strcmp(cmd, "env") == 0)
		|| (ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "pwd") == 0)
		|| (ft_strcmp(cmd, "unset") == 0))
		return (true);
	return (false);
}

char	*final_path(char *cmd, char **path_env)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (path_env[i])
	{
		cmd_path = ft_strjoin(path_env[i], cmd);
		if (!cmd_path)
		{
			ft_putendl_fd("malloc", 2);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_ptr(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_path_env(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

char	**extract_path(t_data *data)
{
	char	**env_path;

	if (search_in_env("PATH", data->env, 4) != -1)
		return (NULL);
	env_path = ft_split(get_path_env(data->env, "PATH"), ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}
