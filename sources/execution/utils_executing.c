/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:39:03 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/24 18:19:33 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int length_env(char **env)
{
    int i = 0;
    while (env[i])
        i++;
    return i;
}*/


bool	check_builtins(char *cmd)
{
    if ((ft_strncmp(cmd, "cd", 3) == 0)
        || (ft_strncmp(cmd, "echo", 5) == 0)
        || (ft_strncmp(cmd, "env", 4) == 0)
        || (ft_strncmp(cmd, "export", 7) == 0)
        || (ft_strncmp(cmd, "pwd", 4) == 0)
        || (ft_strncmp(cmd, "unset", 6) == 0))
        return (true);
    return (false);
}

/* exec command utils */
int	_srch_path(char *envp[])
{
    int		i;
    int		j;
    char	*tab;

    i = 0;
    j = 0;
    tab = "PATH\0";
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] == tab[j] && j <= 4)
            j++;
        if (j == 4)
            return (i);
        i++;
    }
    return (-1);
}

char	**extract_path(char *envp[])
{
    return (ft_split(envp[_srch_path(envp)], ':'));
}

void	_free(char *path[])
{
    int	i;

    i = 0;
    if (path != NULL && *path != NULL)
    {
        while (path[i])
        {
            free(path[i]);
            i++;
        }
    }
    free(path);
}
