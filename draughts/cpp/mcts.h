#ifndef MCTS_H
#define MCTS_H

#include <time.h>
#include <math.h>
#include <algorithm>

#include "play.h"
#include "board.h"

struct Node{
  Node* parent;

  bool next_player;
  int games;
  double reward;

  int nexpanded;
  bool terminal;
  int res;

  Board *board;

  std::vector<Play> lst_plays;
  std::vector<Node*> lst_childs;

  Node(Node *node, bool player, Board *board){
    this->parent = node;
    this->board = board;

    this->next_player = player;
    this->games = 0;
    this->reward = 0;

    this->nexpanded = 0;
    this->terminal = false;
    this->res = 0;
  }

  bool has_childs(){
    return !lst_childs.empty();
  }
};

static void clean(Node *node){
  if(!node) return;

  for(Node *x: node->lst_childs) clean(x);
  delete(node->board);
  delete(node);
}


class MCTS{
public:
  int ngames;
  bool first_player;

  Node* root;
  Board *board;

  MCTS(int time_limit, bool first_player);

  void init(Board *board);

  void search();
  void play(Play p);

  double eval(Node *parent, Node *node, double EXPLOR_PARAM);
  int select_child(Node* node);
  Node* select(Node* node);
  void expand(Node* node);
  int simulate(Board *board, bool player1, int depth, Node *child);
  void backpropagate(Node *node, int res);
  void backpropagate_aux(Node *node, double val);

  void print2poll(){}

};
#endif //MCTS_H
