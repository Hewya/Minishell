/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabarnou <gabarnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:53:16 by gabarnou          #+#    #+#             */
/*   Updated: 2024/06/21 21:11:11 by gabarnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void running(t_data *data)
{
	while (1)
	{
		data->user_input = readline(PROMPT);
		if (data->user_input == NULL || *data->user_input == '\0')
    	{
    	    printf("No input provided\n");
    	    return ;
    	}
		if (parse_user_input(data) == true)
		{
			printf("SUCCESS OF PARSING\n");
		}
		else
			printf("FAILURE OF PARSING\n");
		print_tokens(data->token);
		free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data data;

	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	if(ac != 1)
	{
		usage_msg();
		return (1);
	}
	if (!init_data(&data, env))
	{
		printf("FAILED\n");
		return (1);
	}
	running(&data);
	execute();
	return (0);
}
