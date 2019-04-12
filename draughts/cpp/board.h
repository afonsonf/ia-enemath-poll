#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stack>

#include "play.h"
#include "common.h"

class Board{
public:
	int board[8][8];
	int numberPieces;

	std::stack<Move> movesStack;
	std::stack<Play> playsStack;

	Play best_play;
	int depth;

	Board();
	Board* dup();

	bool validMove(Pos p, int code);

	Pos play_aux(Pos p, int code);
	void rmplay_aux();

	void play(Play p);
	void rmplay();

  bool inBounds(Pos p);
  bool open(Pos p);
  bool jumpOK(Pos p1, Pos p2);

  bool canJump(Pos p);
  bool canStep(Pos p);

	std::vector<Pos> getMovablePieces (bool player1);

	std::vector<Play> getPlays(bool player);

	int whoWins(bool next_player);
	bool isDraw();
	bool gameOver(bool next_player);

	std::vector<std::list<int> > getJumpMoves(Pos p);
	std::vector<std::list<int> > getStepMoves(Pos p);
	std::vector<std::list<int> > getMoves(Pos p);

	int eval_board(int op = 1);
	int eval_board_1();
	int eval_board_2();

	void print_board();
};

#endif // BOARD_H
