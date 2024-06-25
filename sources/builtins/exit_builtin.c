/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapuis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:52:19 by echapuis          #+#    #+#             */
/*   Updated: 2024/06/10 14:52:20 by echapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*

exit [n]
provoque l'arrêt du programme shell avec un code de retour ($?) égal à n.
Si n n'est pas précisé, le code de retour fourni est celui de la dernière commande exécutée.
exit prend seulement des arguments de type entier compris entre 0 et 255 d'où :
long long	code2;
code2 = ft_atoi_exit(args[1], 0, &pbm); // atoi adapté à exit, qui renvoie un long long (voir tests en dessous)
g_status = code2 % 256;

*/

bool    exit_alone(t_data *data)
{
    if (data->cmd)
        return (false);
    if (data->cmd->next || data->cmd->prev)
        return (true);
    return (false);
}


/*
int get_code(t_data *data)
{

}*/

int exit_builtin(t_data *data)
{
    int exit_code;

    exit_code = 0;
    if (exit_alone(data) == false)
        ft_putendl_fd("exit", 1);
    if (data->cmd->args[2])
        ft_putendl_fd("exit ... too many arguments", 1);
    if (!data->cmd->args || !data->cmd->args[1])
        exit_code = /*last exit code */
    else
        exit_code = get_code(data);
    exit_minishell(data, exit_code);
    return (2);
}
