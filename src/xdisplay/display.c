/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:31:56 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/12 20:14:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xdisplay.h"
#include "display.h"
#include "core.h"

int	xplayer_turn(t_c4 **c4, t_board *board)
{
	if ((*c4)->is_player_turn && (*c4)->do_display)
	{
		display_board(board);
		xdisplay_error(&(*c4)->err_str);
		display_info("Please press SPACE on the column you want to play");
		(*c4)->do_display = 0;
	}
	if ((*c4)->move != -1)
	{
		display_board(board);
		xdisplay_error(&(*c4)->err_str);
		display_info("Please press SPACE on the column you want to play");
		if (board->lengths[(*c4)->move] == board->height)
		{
			(*c4)->err_str = ft_strdup("Column filled.");
			if (!(*c4)->err_str)
				return (mlx_loop_end((*c4)->mlx), -1);
			(*c4)->do_display = 1;
		}
		else
			return ((*c4)->move);
		(*c4)->move = -1;
	}
	return (-1);
}

int	x_game_loop(t_c4 **c4)
{
	int		move;
	t_board	*board;

	if ((*c4)->anim || (*c4)->won)
		return (move_anim(c4));
	board = (*c4)->board;
	if (!board->left)
		return (end_game(c4, 'S'), 0);
	if ((*c4)->is_player_turn)
	{
		move = xplayer_turn(c4, board);
		if (move != -1)
		{
			do_move(c4, board, (*c4)->is_player_turn, move);
			(*c4)->err_str = NULL;
		}
	}
	else
	{
		display_board(board);
		display_info("IA is choosing...");
		move = ai_turn(board);
		do_move(c4, board, (*c4)->is_player_turn, move);
	}
	return (0);
}

int	xdisplay(t_board *board)
{
	t_c4	*c4;

	c4 = (t_c4 *)ft_calloc(1, sizeof(t_c4));
	if (!c4)
		return (free_board(board), 1);
	c4->board = board;
	if (ft_init(&c4))
		return (free(c4), 1);
	mlx_hook(c4->win, 17, 1L << 17, red_cross_close, &c4);
	mlx_key_hook(c4->win, e_key_down, &c4);
	mlx_loop_hook(c4->mlx, x_game_loop, &c4);
	mlx_loop(c4->mlx);
	ft_close(&c4);
	return (0);
}
