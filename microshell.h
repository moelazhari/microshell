/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:51:21 by mazhari           #+#    #+#             */
/*   Updated: 2022/12/22 18:29:44 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_cmd
{
	int					prev_pipe[2];
	int					next_pipe[2];
	char				**args;
	struct s_cmd_node	*prev;
	struct s_cmd_node	*next;
}				t_cmd;