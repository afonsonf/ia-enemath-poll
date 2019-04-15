#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "board.h"
#include "common.h"

class Human{
public:
  bool first_player;

  Board *board;
  bool player;

  Human(bool first_player);

  void init(Board *board);
  void play(Play p);

  int getInput(int sz);
  void search();
  bool inRange(int x, int i, int j);

  void print2poll();
  void boardPrint();
  void playsPrint();
  void lastPrint();
};

#endif // HUMAN_H
