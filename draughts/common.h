#ifndef COMMON_H
#define COMMON_H

#define valueOfKing 5

struct Pos{
  int i;
  int j;

  inline int operator< (Pos b){
    if(i==b.i) return j<b.j;
    return i<b.i;
  }

  inline bool operator==(const Pos& p1){
      return p1.i == this->i && p1.j == this->j;
  }
};

static Pos mk_Pos(int i, int j){
  Pos p;
  p.i = i, p.j = j;
  return p;
}

struct Move{
  Pos last_pos;
  int last_code;
  int last_eat;
  bool last_up;
};

static int sign(int val) {
  if (val > 0) return 1;
  if (val < 0) return -1;
  return 0;
}

#endif //COMMON_H
