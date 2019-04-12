#include "human.h"

Human::Human(bool first_player){
  this->first_player = first_player;
}

void Human::init(Board *board){
  this->board = board;
  player = first_player;
}

void Human::play(Play p){
  player = !player;
}

int Human::getInput(int sz){
  int index = -1;
  while(1){
      printf("Choose a move: "); fflush(stdout);
      scanf("%d",&index);

      if(!inRange(index,0,sz-1)) printf("Invalid move\n");
      else break;
  }
  return index;
}

void Human::search(){
  int index = -1;

  auto lst_plays = board->getPlays(player);
  int sz = lst_plays.size();

  printIndex();

  char s[1000];
  memset(s, '\0', sizeof s);
  while(strcmp(s,"y") && strcmp(s,"yes")){
    board->print_board();
    for(int i=0;i<sz;i++){
      printf("%d: ",i);
      printPlay(lst_plays[i]);
    }printf("\n");
    index = getInput(sz);
    board->play(lst_plays[index]);
    board->print_board();
    board->rmplay();

    memset(s, '\0', sizeof s);
    printf("This one? ");fflush(stdout);
    scanf("%s",s);
  }


  board->best_play = lst_plays[index];
}

void Human::printIndex(){
  printf("Code 0 - step up left\n");
  printf("Code 1 - step up right\n");
  printf("Code 2 - jump up left\n");
  printf("Code 3 - jump up right\n");
  printf("Code 4 - step down left\n");
  printf("Code 5 - step down right\n");
  printf("Code 6 - jump down left\n");
  printf("Code 7 - jump down right\n");
  printf("\n");
}

bool Human::inRange(int x, int i, int j){
  return x>=i && x<=j;
}
