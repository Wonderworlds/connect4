/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:08:07 by jraffin           #+#    #+#             */
/*   Updated: 2022/06/12 16:47:16 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "core.h"
#include "display.h"

int	arg_check(int argc, char **argv, int *width, int *height)
{
	if (argc != 3)
		return (ft_putstr_fd("wrong number of argument.\n\t\
USAGE : ./connect4 [height] [width]", 1), 0);
	if (ft_atoi_err(argv[1], height) || *height < 6)
		return (ft_putstr_fd("invalid height (must be a valid \
integer >= 6)", 1), 0);
	if (ft_atoi_err(argv[2], width) || *width < 7)
		return (ft_putstr_fd("invalid width (must be a valid \
integer >= 7)", 1), 0);
	if (*width > (INT_MAX / *height))
		return (ft_putstr_fd("width * height product must be <= INT_MAX"
		, 1), 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_board	board;

	if (arg_check(argc, argv, &board.width, &board.height))
		return (1);
	if (init_board(&board))
		return (ft_putstr_fd("Error : couldn't \
allocate memory !", 1), 1);
	game_loop(&board);
	free_board(&board);
	return (0);
}
