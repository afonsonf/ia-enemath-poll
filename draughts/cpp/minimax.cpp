#include "minimax.h"

#include <time.h>
#include <stdlib.h>

Minimax::Minimax(int depth, bool first_player, int option /*= 1*/){
  this->depth = depth;
  this->first_player = first_player;
  this->option = option;
  srand(42);
}

void Minimax::init(Board *board){
  this->board = board;
  this->player = this->first_player;
}

void Minimax::play(Play p){
  player = !player;
}

//best move saved in board
void Minimax::search(){

  auto plays = board->getPlays(player);
  board->best_play = plays[0];

  //[TODO] test if wins next move

  int alfa = INT_MIN;
  int beta = INT_MAX;

  if(player) //if we are player1, we want to maximize the board score
  max_value(board,alfa,beta,depth);
  else //if we are not player1, we want to minimize the board score
  min_value(board,alfa,beta,depth);
}

int Minimax::max_value(Board *board, int alfa, int beta, int depth_max)
{
  if(board->gameOver(true)){
    if(board->whoWins(true)) return -1000000;
    return 0;
  }

  if (board->depth >= depth_max) return board->eval_board(option);

  int val = INT_MIN, valx;
  int podar = 0;

  auto plays = board->getPlays(true);

  std::random_shuffle(plays.begin(), plays.end());

  for(Play p : plays){ if(podar) break;

    //play
    board->play(p);

    //call min
    board->depth++;
    valx = min_value(board, alfa, beta, depth_max);
    board->depth--;

    //rmplay
    board->rmplay();

    //process valx
    if (val < valx){
      if (board->depth == 0) board->best_play = p;
      val = valx;
    }

    if (val>=beta){
      podar=1;
    }

    alfa = std::max (alfa,val);
  }

  return val;
}

int Minimax::min_value(Board *board, int alfa, int beta, int depth_max)
{
  if(board->gameOver(false)){
    if(board->whoWins(false)) return 1000000;
    return 0;
  }
  if ( board->depth >= depth_max) return board->eval_board(option);

  int val = INT_MAX, valx;
  int podar = 0;

  auto plays = board->getPlays(false);

  std::random_shuffle(plays.begin(),plays.end());

  for(Play p : plays){ if(podar) break;
    //play
    board->play(p);

    //call min
    board->depth++;
    valx = max_value(board, alfa, beta, depth_max);
    board->depth--;

    //rmplay
    board->rmplay();

    //process valx
    if (val > valx){
      if (board->depth == 0) board->best_play = p;
      val = valx;
    }

    if (val<=alfa){
      podar=1;
    }

    beta = std::min (beta,val);
  }

  return val;
}
