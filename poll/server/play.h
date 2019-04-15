#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <list>

#include "common.h"

struct Play{
  Pos piece;
  std::list<int> codes;

  inline bool operator==(const Play& p1){
    if(!(this->piece == p1.piece)) return false;
    if(p1.codes.size() != this->codes.size()) return false;

    auto it1 = p1.codes.begin();
    auto it2 = this->codes.begin();
    for(;it1!=p1.codes.end() && it2!=this->codes.end();it1++,it2++){
      if(*it1 != *it2) return false;
    }

    return true;
  }
};

static void printPlay(Play p){
  printf("(%d, %d)", p.piece.j, p.piece.i);
  for(int code: p.codes) printf(" %d",code);
  printf("\n");
}

#endif // PLAY_H
