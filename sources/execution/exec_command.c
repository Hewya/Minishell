/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:36 by echapuis          #+#    #+#             */
/*   Updated: 2024/09/29 17:39:14 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(t_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL && search_in_env("PATH", data->env,
			4) != -1)
	{
		ft_putstr_fd(cmd->command, 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	if (access(cmd->command, F_OK) != 0)
	{
		ft_putstr_fd(cmd->command, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	else if (is_directory(cmd->command))
	{
		ft_putstr_fd(cmd->command, 2);
		ft_putendl_fd("Is a directory", 2);
		return (126);
	}
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (126);
	return (EXIT_SUCCESS);
}

char	*get_cmd_path(t_data *data, char *command)
{
	char	**paths_env;
	char	*cmd;
	char	*cmd_path;

	if (!command)
		return (NULL);
	paths_env = extract_path(data);
	if (!paths_env)
		return (NULL);
	cmd = ft_strjoin("/", command);
	if (!cmd)
	{
		free_str_tab(paths_env);
		return (NULL);
	}
	cmd_path = final_path(cmd, paths_env);
	if (!cmd_path)
	{
		free_ptr(cmd);
		free_str_tab(paths_env);
		return (NULL);
	}
	return (cmd_path);
}

int	exec_with_path(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (127);
	if (is_directory(cmd->command))
		return (127);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (127);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		return (CMD_NOT_FOUND);
	return (EXIT_FAILURE);
}

int	launch_command(t_data *data, t_command *cmd)
{
	int	res;

	res = check_command(data, cmd);
	if (res != 0)
		return (res);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errno);
	return (EXIT_FAILURE);
}
