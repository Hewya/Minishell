/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:36 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/23 18:37:15 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	_launch_command(char *pn, t_data *data, char **env)
{
	int	fd;

	if (access(pn, F_OK) != 0)
		return (0);
	fd = open(pn, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ft_putstr_fd(data->cmd->command, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (1);
	}
	if (access(pn, X_OK) == 0)
	{
		execve(pn, data->cmd->args, env);
		perror(pn);
	}
	else
		ft_putstr_fd(data->cmd->command, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (1);
}

char	**_final_path(char **ext_path)
{
	int		i;
	char	**path;

	i = 0;
	while (ext_path[i++])
		;
	path = malloc(sizeof(char *) * (i + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (ext_path[i])
	{
		path[i] = ft_strjoin(ext_path[i], "/");
		if (path[i++])
			continue ;
		_free(path);
		return (NULL);
	}
	path[i] = NULL;
	return (path);
}

int	_with_path(t_data *data, char **env)
{
	char	**ext_path;
	char	**itr;
	char	**path;
	char	*absolute_path;

	ext_path = extract_path(env);
	if (!ext_path)
		return (_free(data->cmd->args), 1);
	path = _final_path(ext_path);
	_free(ext_path);
	itr = path;
	while (*itr)
	{
		absolute_path = ft_strjoin(*itr++, data->cmd->command);
		if (absolute_path == NULL)
			return (_free(path), 1);
		if (_launch_command(absolute_path, data, env))
			return (free(absolute_path), _free(path), 1);
		free(absolute_path);
	}
	return (_free(path), 0);
}

void	call_exec(t_data *data)
{
	if (ft_strchr(data->cmd->command, '/') == NULL && _srch_path(data->env) !=
		-1)
		if (_with_path(data, data->env))
			return ;
	if (_launch_command(data->cmd->command, data, data->env))
		return ;
	ft_putstr_fd(data->cmd->command, 2);
	if (ft_strchr(data->cmd->command, '/'))
		ft_putendl_fd(": command not found", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
}
