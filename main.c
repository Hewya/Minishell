/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:16 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/19 20:25:17 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	running_minishell(t_data *data)
{
	while (true)
	{
		data->user_input = readline(PROMPT);
		parse_user_input(data);
		print_token_list(t_token **tokens);
		print_token_type(t_token *token, char *prefix);
		print_cmds_list(t_data *data);
		print_cmd_args(t_command *command);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if(ac != 1 || !init_data(&data, env))
	{
		printf("FAILED\n");
		if (ac != 1)
			usage_msg();
		return (1);
	}
	printf("OK STARTING...\n");
	running_minishell(&data);
	return (0);
}
