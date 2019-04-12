#include "board.h"

//values growing [NOTE change eval function to use]
int values_2[8][8] = {
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6},
  {1, 1, 1, 3, 3, 5, 5, 6}
};

//copied from example
int values_[8][8] = {
  {4, 4, 4, 4, 4, 4, 4, 4},
  {4, 3, 3, 3, 3, 3, 3, 3},
  {4, 3, 2, 2, 2, 2, 2, 2},
  {4, 3, 2, 1, 1, 2, 3, 4},
  {4, 3, 2, 1, 1, 2, 3, 4},
  {4, 3, 2, 2, 2, 2, 2, 2},
  {4, 3, 3, 3, 3, 3, 3, 3},
  {4, 4, 4, 4, 4, 4, 4, 4}
};

int values_1[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

//two values [NOTE change eval function to use]
int values_a[8][8] = {
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3},
  {1, 1, 1, 1, 3, 3, 3, 3}
};

//to prevent kings loop in the edges
int valuesKing[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 3, 3, 3, 3, 1, 1},
  {1, 1, 3, 4, 4, 3, 1, 1},
  {1, 1, 3, 4, 4, 3, 1, 1},
  {1, 1, 3, 3, 3, 3, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

//constructor
Board::Board(){
  memset(board, 0, sizeof board);

  for(int a = 0; a < 8; a++){
    for(int b = 0; b < 8; b++){
      if(b < 3 && (b + a) % 2 == 0){
        board[a][b] = 1;
        numberPieces++;
      }
      else if(b > 4 && (b + a)%2 == 0){
        board[a][b] = -1;
        numberPieces++;
      }
      else{
        board[a][b] = 0;
      }
    }
  }

  depth = 0;
}

Board* Board::dup(){
  Board *res = new Board();

  for(int i=0;i<8;i++) for(int j=0;j<8;j++) res->board[i][j] = board[i][j];
  res->numberPieces = numberPieces;

  return res;
}

bool Board::validMove(Pos p, int code){
  if(!inBounds(p)){
    printf("Error: pos not in bounds (%d,%d)\n",p.i,p.j); return false;
  }
  if(open(p)){
    printf("Error: no piece in pos (%d,%d)\n",p.i,p.j); return false;
  }

  if(code == 0 && !open(mk_Pos(p.i-1,p.j+1))){
    printf("Error: try step right up, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 1 && !open(mk_Pos(p.i+1,p.j+1))){
    printf("Error: try step right down, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 4 && !open(mk_Pos(p.i-1,p.j-1))){
    printf("Error: try step left up, pos not open (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 5 && !open(mk_Pos(p.i+1,p.j-1))){
    printf("Error: try step left down, pos not open (%d,%d)\n",p.i,p.j); return false;
  }

  if(code == 2 && !jumpOK(p,mk_Pos(p.i-1,p.j+1))){
    printf("Error: try jump right up, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 3 && !jumpOK(p,mk_Pos(p.i+1,p.j+1))){
    printf("Error: try jump right down, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 6 && !jumpOK(p,mk_Pos(p.i-1,p.j-1))){
    printf("Error: try jump left up, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  if(code == 7 && !jumpOK(p,mk_Pos(p.i+1,p.j-1))){
    printf("Error: try jump left down, jump not ok (%d,%d)\n",p.i,p.j); return false;
  }
  return true;
}

//play piece of player
Pos Board::play_aux(Pos p, int code){
  if(!validMove(p,code)){
    print_board(); exit(1);
  }

  Move mv;

  int value = board[p.i][p.j];
  board[p.i][p.j] = 0;
  switch(code){
    case(0):{ //step right up
      p.i --; p.j ++;
      break;
    }
    case(1):{ //step right down
      p.i ++; p.j ++;
      break;
    }
    case(2):{ //jump right up
      mv.last_eat = board[p.i-1][p.j+1];
      board[p.i-1][p.j+1] = 0;
      p.i -= 2; p.j += 2;
      numberPieces--;
      break;
    }
    case(3):{ //jump right down
      mv.last_eat = board[p.i+1][p.j+1];
      board[p.i+1][p.j+1] = 0;
      p.i += 2; p.j += 2;
      numberPieces--;
      break;
    }
    case(4):{ //step left up
      p.i --; p.j --;
      break;
    }
    case(5):{ //step left down
      p.i ++; p.j --;
      break;
    }
    case(6):{ //jump left up
      mv.last_eat = board[p.i-1][p.j-1];
      board[p.i-1][p.j-1] = 0;
      p.i -= 2; p.j -= 2;
      numberPieces--;
      break;
    }
    case(7):{ //jump left down
      mv.last_eat = board[p.i+1][p.j-1];
      board[p.i+1][p.j-1] = 0;
      p.i += 2; p.j -= 2;
      numberPieces--;
      break;
    }
    default: printf("Error cod\n"); exit(1); break;
  }

  board[p.i][p.j] = value;
  if((p.j == 0 && value == -1) || (p.j == 7 && value == 1)){  //king it
    board[p.i][p.j] *= valueOfKing;
    mv.last_up = true;
  }
  else mv.last_up = false;

  mv.last_pos = p;
  mv.last_code = code;

  movesStack.push(mv);

  return p;
}

//undo last play
void Board::rmplay_aux(){

  Move mv = movesStack.top();
  movesStack.pop();

  int value = board[mv.last_pos.i][mv.last_pos.j];
  board[mv.last_pos.i][mv.last_pos.j] = 0;

  if(mv.last_up) value /= valueOfKing;

  switch(mv.last_code){
    case(0):{ //step right up
      mv.last_pos.i ++; mv.last_pos.j --;
      break;
    }
    case(1):{ //step right down
      mv.last_pos.i --; mv.last_pos.j --;
      break;
    }
    case(2):{ //jump right up
      mv.last_pos.i += 2; mv.last_pos.j -= 2;
      board[mv.last_pos.i-1][mv.last_pos.j+1] = mv.last_eat;
      numberPieces++;
      break;
    }
    case(3):{ //jump right down
      mv.last_pos.i -= 2; mv.last_pos.j -= 2;
      board[mv.last_pos.i+1][mv.last_pos.j+1] = mv.last_eat;
      numberPieces++;
      break;
    }
    case(4):{ //step left up
      mv.last_pos.i ++; mv.last_pos.j ++;
      break;
    }
    case(5):{ //step left down
      mv.last_pos.i --; mv.last_pos.j ++;
      break;
    }
    case(6):{ //jump left up
      mv.last_pos.i += 2; mv.last_pos.j += 2;
      board[mv.last_pos.i-1][mv.last_pos.j-1] = mv.last_eat;
      numberPieces++;
      break;
    }
    case(7):{ //jump left down
      mv.last_pos.i -= 2; mv.last_pos.j += 2;
      board[mv.last_pos.i+1][mv.last_pos.j-1] = mv.last_eat;
      numberPieces++;
      break;
    }
    default: break;
  }

  board[mv.last_pos.i][mv.last_pos.j] = value;

}

void Board::play(Play p){
  Pos piece = p.piece;
  for(int code: p.codes){
    piece = play_aux(piece,code);
  }
  playsStack.push(p);
}

void Board::rmplay(){
  Play p = playsStack.top();
  playsStack.pop();

  for(int i=0;i<(int)p.codes.size();i++)rmplay_aux();
}

// pos inside board
bool Board::inBounds(Pos p){
  return p.i >= 0 && p.i < 8 && p.j >= 0 && p.j < 8;
}

// pos empty
bool Board::open(Pos p){
  return inBounds(p) && board[p.i][p.j] == 0;
}

// test if piece p1 can jump piece p2
bool Board::jumpOK(Pos p1, Pos p2){
  return open(mk_Pos(2*p2.i - p1.i,2*p2.j - p1.j)) && inBounds(p2) && (sign(board[p1.i][p1.j]) == -sign(board[p2.i][p2.j]));
}

bool Board::canJump(Pos p){
  int pieceType = board[p.i][p.j];
  if((pieceType > 0 || pieceType == -valueOfKing) && (jumpOK(p, mk_Pos(p.i-1,p.j+1)) || jumpOK(p, mk_Pos(p.i+1,p.j+1)))){  //check jumps in the positive direction
    return true;
  }
  if((pieceType < 0 || pieceType == valueOfKing) &&(jumpOK(p, mk_Pos(p.i-1,p.j-1)) || jumpOK(p, mk_Pos(p.i+1,p.j-1)))){  //check jumps in the negative direction
    return true;
  }
  return false;
}

bool Board::canStep(Pos p){
  int pieceType = board[p.i][p.j];
  if((pieceType > 0 || pieceType == -valueOfKing) && (open(mk_Pos(p.i-1,p.j+1)) || open(mk_Pos(p.i+1,p.j+1)))){  //check steps in the positive direction
    return true;
  }
  if((pieceType < 0 || pieceType == valueOfKing) &&(open(mk_Pos(p.i-1,p.j-1)) || open(mk_Pos(p.i+1,p.j-1)))){  //check steps in the negative direction
    return true;
  }
  return false;
}

std::vector<Pos> Board::getMovablePieces (bool player1){
  std::vector<Pos> res;
  Pos px;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      px.i = i, px.j = j;
      if(sign(board[i][j]) == (player1 ? 1 : -1) && canJump(px))
      res.push_back(px);
    }
  }

  if(res.empty()){
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        px.i = i, px.j = j;
        if(sign(board[i][j]) == (player1 ? 1 : -1) && canStep(px))
        res.push_back(px);
      }
    }
  }

  return res;
}

std::vector<Play> Board::getPlays(bool player){
  std::vector<Play> res;
  std::vector<Pos> pieces = getMovablePieces(player);
  std::vector<std::list<int> > moves;

  Play play;
  for(Pos p : pieces){
    moves = getMoves(p);
    for(std::list<int> codes: moves){
      play.piece = p;
      play.codes = codes;

      res.push_back(play);
    }
  }

  return res;
}

int Board::whoWins(bool next_player){
  if(getMovablePieces(next_player).empty()){
    if(next_player) return -1;
    return 1;
  }
  return 0;
}

bool Board::isDraw(){return false;}

bool Board::gameOver(bool next_player){
  if(whoWins(next_player) || isDraw()) return true;
  return false;
}

std::vector<std::list<int> > Board::getJumpMoves(Pos p){
  std::vector<std::list<int> > moves;
  std::vector<std::list<int> > mx;
  int pieceType = board[p.i][p.j];

  Pos px;

  if(pieceType > 0 || pieceType == -valueOfKing){
    if(jumpOK(p, mk_Pos(p.i-1,p.j+1))){
      //(2);
      px = play_aux(p, 2);
      mx = getJumpMoves(px);
      rmplay_aux();

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(2);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(2);
          moves.push_back(mx[i]);
        }
      }

    }
    if(jumpOK(p, mk_Pos(p.i+1,p.j+1))){
      //(3);

      px = play_aux(p, 3);
      mx = getJumpMoves(px);
      rmplay_aux();

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(3);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(3);
          moves.push_back(mx[i]);
        }
      }
    }
  }
  if(pieceType < 0 || pieceType == valueOfKing){
    if(jumpOK(p, mk_Pos(p.i-1,p.j-1))){
      //(6);

      px = play_aux(p, 6);
      mx = getJumpMoves(px);
      rmplay_aux();

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(6);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(6);
          moves.push_back(mx[i]);
        }
      }
    }
    if(jumpOK(p, mk_Pos(p.i+1,p.j-1))){
      //(7);

      px = play_aux(p, 7);
      mx = getJumpMoves(px);
      rmplay_aux();

      if((int)mx.size() == 0){
        moves.push_back(std::list<int>());
        moves.back().push_back(7);
      }
      else {
        for(int i=0;i<(int)mx.size();i++){
          mx[i].push_front(7);
          moves.push_back(mx[i]);
        }
      }
    }
  }
  return moves;
}

std::vector<std::list<int> > Board::getStepMoves(Pos p){
  std::vector<std::list<int> > moves;
  int pieceType = board[p.i][p.j];

  if(pieceType > 0 || pieceType == -valueOfKing){
    if(open(mk_Pos(p.i-1,p.j+1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(0);
    }
    if(open(mk_Pos(p.i+1,p.j+1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(1);
    }
  }
  if(pieceType < 0 || pieceType == valueOfKing){
    if(open(mk_Pos(p.i-1,p.j-1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(4);
    }
    if(open(mk_Pos(p.i+1,p.j-1))){
      moves.push_back(std::list<int>());
      moves.back().push_back(5);
    }
  }

  return moves;
}

std::vector<std::list<int> > Board::getMoves(Pos p){
  if(canJump(p))
  return getJumpMoves(p);

  if(canStep(p))
  return getStepMoves(p);
}

int Board::eval_board_1(){
  int value = 0;
  for(int i=0;i<8;i++){
    for(int j=0; j<8;j++){
      if(std::abs(board[i][j]) == valueOfKing)
        value += valuesKing[i][j] * board[i][j];
      else if(sign(board[i][j]) > 0){
        value += values_1[i][j] * board[i][j];
      }
      else if(sign(board[i][j]) < 0){
        value += values_1[i][7-j] * board[i][j];
      }
    }
  }
  return value;
}

int Board::eval_board_2(){
  int value = 0;
  for(int i=0;i<8;i++){
    for(int j=0; j<8;j++){
      if(std::abs(board[i][j]) == valueOfKing)
        value += valuesKing[i][j] * board[i][j];
      else if(sign(board[i][j]) > 0){
        value += values_2[i][j] * board[i][j];
      }
      else if(sign(board[i][j]) < 0){
        value += values_2[i][7-j] * board[i][j];
      }
    }
  }
  return value;
}

int Board::eval_board(int op /*=1*/){
  if(op==1) return eval_board_1();
  else return eval_board_2();
}


//print board pretty
void Board::print_board(){
  printf(" | "); for(int i=0;i<8;i++)printf("%d ",i); printf("|\n");
  printf(" | "); for(int i=0;i<8;i++)printf("--"); printf("|\n");
  for(int j=7;j>=0;j--){
    printf("%d| ",j);
    for(int i=0;i<8;i++){
      switch(board[i][j]){
        case -valueOfKing:{printf("R "); break;}
        case -1:{printf("r "); break;}
        case  0:{printf("_ "); break;}
        case  1:{printf("b "); break;}
        case valueOfKing:{printf("B "); break;}

        default:
        printf("Error board: (%d,%d) %d\n",i,j,board[i][j]); exit(1);
      }
    }
    printf("|%d\n",j);
  }
  printf(" | "); for(int i=0;i<8;i++)printf("--"); printf("|\n");
  printf(" | "); for(int i=0;i<8;i++)printf("%d ",i); printf("|\n\n");
}
