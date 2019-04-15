#include <stdio.h>
#include <signal.h>

#include "board.h"
#include "minimax.h"
#include "mcts.h"
#include "human.h"

#define SEE true

void handler_function(int sig){}

int main(){
  signal(SIGINT, handler_function);

  Board *board;
  bool first_player = true;

  /*-----------------------------------------------------------*/

  // MCTS *p1 = new MCTS(100000, first_player);
  // MCTS *p2 = new MCTS(100000, first_player);

  // Minimax *p1 = new Minimax(12,first_player, 1);
  Minimax *p2 = new Minimax(10,first_player, 1);

  Human *p1 = new Human(first_player);
  // Human *p2 = new Human(first_player);

  /*-----------------------------------------------------------*/

  bool player;

  int ngames=1,w=0,d=0,l=0,plays,win;
  while(ngames--){
    //if(board) delete(board);
    board = new Board();

    player = first_player;

    p1->init(board);
    p2->init(board);

    plays=0;
    if(SEE) board->print_board();
    while(1){
      if(board->gameOver(player)){
        win = board->whoWins(player);
        if(win == -1){
          l++;
          printf("R wins (%2d::%2d::%2d) %d\n",w,d,l,plays);
        }
        else if(win == 1){
          w++;
          printf("B wins (%2d::%2d::%2d) %d\n",w,d,l,plays);
        }
        else{
          d++;
          printf("draw   (%2d::%2d::%2d)\n",w,d,l);
        }

        p1->print2poll();
        p2->print2poll();
        break;
      }

      if(plays>500){
        d++;
        printf("draw   (%2d::%2d::%2d)\n",w,d,l);
        break;
      }

      if(player) p1->search();
      else p2->search();

      if(SEE){
        if(player) printf("B plays\n");
        else       printf("R plays\n");
      }

      board->play(board->best_play);
      p1->play(board->best_play);
      p2->play(board->best_play);

      if(SEE)board->print_board();

      player = !player;
      plays++;
    }
    delete(board);
  }

  printf("w: %d\nd: %d\nl: %d\n",w,d,l);

  return 0;
}
