/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:16 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/20 21:39:16 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void running(t_data *data)
{
	data->user_input = readline(PROMPT);
	if (parse_user_input(data) == true)
		printf("SUCCESS OF PARSING\n");
	else
		printf("FAILURE OF PARSING\n");
}

int	main(int ac, char **env)
{
	t_data data;

	ft_memset(&data, 0, sizeof(t_data));
	if(ac != 1 || !init_data(&data, env))
	{
		usage_msg();
		return (1);
	}
	if (!init_data(&data, env))
	{
		printf("FAILED\n");
		return (1);
	}
	execute();
	running(&data);
	return (0);
}
