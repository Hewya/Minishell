/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:47:15 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/25 01:02:10 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args(char *args[])
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char *ft_getenv(char **env, const char *name)
{
	int i;
	size_t len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	 return (NULL);
 }

 void change_env_var(char **env, const char *name, const char *value)
 {
	 int len;
	 int i;
	 char *new_var;

	 i = 0;
	 len = ft_strlen(name);
	 while (env[i])
	 {
		 if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		 {
			 free(env[i]);
			 new_var = malloc((len + ft_strlen(value) + 2)*sizeof(char*));
			 if (!new_var)
			 {
				 printf("malloc failed\n");
				 return;
			 }
			 strcpy(new_var, name);
			 strcat(new_var, "=");
			 strcat(new_var, value);
			 env[i] = new_var;
			 return;
		 }
		 i++;
	 }
	 new_var = malloc(len + ft_strlen(value) + 2);
	 if (!new_var)
	 {
		 printf("malloc failed\n");
		 return;
	 }
	 strcpy(new_var, name);
	 strcat(new_var, "=");
	 strcat(new_var, value);
	 env[i] = new_var;
	 env[i + 1] = NULL;
 }

void change_pwd(t_data *data)
{
	char cwd[1024];
	char *oldpwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		oldpwd = ft_getenv(data->env, "PWD");
		if (oldpwd)
			change_env_var(data->env, "OLDPWD", oldpwd);
		change_env_var(data->env, "PWD", cwd);
	}
	else
		perror("getcwd");
 }

int change_directory(t_data *data)
{
	char *home;
	t_command *cmd;

	home = ft_getenv(data->env, "HOME");
	cmd = data->cmd;

	if (count_args(cmd->args) > 0 && chdir(cmd->args[0]) != -1)
	{
		change_pwd(data);
		return (0);
	}
	else if (count_args(cmd->args) == 0 || ft_strcmp(cmd->args[0], "") == 0)
	{
		if (home != NULL && chdir(home) != -1)
		{
			change_pwd(data);
			return (0);
		}
		else
			 return (-1);
	 }
	 printf("cd: %s: No such file or directory\n", cmd->args[0]);
	 return (-1);
 }

 int cd_builtin(t_data *data)
 {
	 t_command *cmd;

	 cmd = data->cmd;
	 if (count_arg(cmd->args) > 1)
	 {
		 printf("cd: too many arguments\n");
		 return (1);
	 }
	 else
		 return (change_directory(data));
 }

/*
 int main(int argc, char **argv) {
	 (void)argc;
	 (void)argv;
	 t_data data;
	 t_command cmd;
	 char *args[] = {
		 "libft",
		 NULL
	};
	 char *env[] = {
		 "PATH=/usr/bin",
		 "PWD=/home/",
		 "USER=test_user",
		 "HOME=/home/test_user",
		 NULL
	 };

	 data.env = env;
	 data.cmd = &cmd;

	 cmd.command = "cd";
	 cmd.args = args;  // Skip the program name
	 cmd.io_fds = NULL;

	 if (cd(&data) == 0)
	 {
		printf("Directory changed successfully.\n");
		printf("%s\n",getcwd(NULL, 0));

	 }
	 else
		 printf("Failed to change directory.\n");

	 return (0);
 }*/
