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

void Human::boardPrint(){
  printf("[");
  for(int j=7;j>0;j--){
    printf("[");
    for(int i=0;i<7;i++)printf("%d,",board->board[i][j]);
    printf("%d],",board->board[7][j]);
  }
  printf("[");
  for(int i=0;i<7;i++)printf("%d,",board->board[i][0]);
  printf("%d]",board->board[7][0]);
  printf("]\n");
}

void Human::playsPrint(){
  auto lst_plays = board->getPlays(player);
  int sz = lst_plays.size();

  printf("[");
  for(int i=0;i<sz-1;i++){
    std::vector<Pos> v;

    Pos piece = lst_plays[i].piece;
    v.push_back(piece);

    for(int code :lst_plays[i].codes){
      piece = board->play_aux(piece,code);
      v.push_back(piece);
    }
    for(int code :lst_plays[i].codes) board->rmplay_aux();

    int sz2 = (int)v.size();
    printf("[");
    for(int j=0;j<sz2-1;j++){
      char c = 'A'+v[j].i;
      printf("\"%c%d\",",c,v[j].j+1);
    }
    char c = 'A'+v[sz2-1].i;
    printf("\"%c%d\"],",c,v[sz2-1].j+1);
  }
  std::vector<Pos> v;

  Pos piece = lst_plays[sz-1].piece;
  v.push_back(piece);

  for(int code :lst_plays[sz-1].codes){
    piece = board->play_aux(piece,code);
    v.push_back(piece);
  }
  for(int code :lst_plays[sz-1].codes) board->rmplay_aux();

  int sz2 = (int)v.size();
  printf("[");
  for(int j=0;j<sz2-1;j++){
    char c = 'A'+v[j].i;
    printf("\"%c%d\",",c,v[j].j+1);
  }
  char c = 'A'+v[sz2-1].i;
  printf("\"%c%d\"]",c,v[sz2-1].j+1);
  printf("]\n");

  return;
}

void Human::search(){
  int index = -1;

  auto lst_plays = board->getPlays(player);
  int sz = lst_plays.size();

  printf("\n");
  boardPrint();
  playsPrint();
  printf("\n");

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
/*
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
}*/

bool Human::inRange(int x, int i, int j){
  return x>=i && x<=j;
}
