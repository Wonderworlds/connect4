/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:38:02 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/12 23:34:09 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "core.h"
#include "display.h"

static void	game_end(int won, int is_player_turn)
{
	if (!won)
		ft_putstr_fd("\x1b[33mIt's a draw.\x1b[0m\n", 1);
	else if (is_player_turn)
		ft_putstr_fd("\x1b[32mCongratulations you win !\x1b[0m\n", 1);
	else
		ft_putstr_fd("\x1b[31mSorry you lost ...\x1b[0m\n", 1);
}

int	game_loop(t_board *board)
{
	int		is_player_turn;
	int		move;
	int		won;

	is_player_turn = board->token[1] == YEL_CHAR;
	display_board(board);
	while (board->left)
	{
		if (is_player_turn)
			move = player_turn(board);
		else
			move = ai_turn(board);
		if (move == -1)
			return (ft_putstr_fd("Error reading stdin\n", 2), 1);
		board->map[move][board->lengths[move]++] = board->token[is_player_turn];
		--board->left;
		display_board(board);
		won = is_won(board, move);
		if (won)
			break ;
		else
			is_player_turn = !is_player_turn;
	}
	game_end(won, is_player_turn);
	return (0);
}
