/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:16 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/26 20:23:34 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	running(t_data *data)
{
	while (1)
	{
		data->user_input = readline(PROMPT);
		if (data->user_input == NULL)
			return ;
		if (data->user_input != NULL && *data->user_input != '\0')
		{
			if (parse_user_input(data) == true)
				data->last_exit_code = executing(data);
		}
		else
			data->last_exit_code = 1;
		free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	rl_outstream = stderr;
	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 1)
		usage_msg();
	if (!init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	running(&data);
	exit_shell(&data, data.last_exit_code);
	return (0);
}
