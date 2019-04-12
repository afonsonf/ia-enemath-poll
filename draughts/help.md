input de um move: (e/d) (u/d)
no max 4 jogadas possiveis, esquerda/direita, cima/baixo
rainha pode andar 1 casa para tras

numerar posicoes
(d,u) - 0
(d,d) - 1
(e,d) - 2
(e,u) - 3

eval > pos para player1

passar eval para minimax
simplificar minimax !?

vhdbfgv
1_1 || 1_3_5_6
1_3

mcts(50) 500000 vs minimax 4, 1 minimax
w: 121
d: 28
l: 51

mcts(50) 200000 vs minimax 4, 1 minimax
w: 112
d: 34
l: 54

mcts(50) 100000 vs minimax 4, 1 minimax
w: 107
d: 36
l: 57

mcts(50) 50000 vs minimax 4, 1 minimax
w: 78
d: 58
l: 64



w: 79
d: 55
l: 66






void Human::printIndex(){
  printf("Code 0 - step right up\n");
  printf("Code 1 - step right down\n");
  printf("Code 2 - jump right up\n");
  printf("Code 3 - jump right down\n");
  printf("Code 4 - step left up\n");
  printf("Code 5 - step left down\n");
  printf("Code 6 - jump left up\n");
  printf("Code 7 - jump left down\n");
  printf("\n");
}



/*
int best_i = 0, most_plays, most_wins;
int sz = (int)root->lst_childs.size();

for(int i=0;i<sz;i++){
  child = root->lst_childs[i];
  if(child->wins > most_wins){
      best_i = i;
      most_plays = child->games;
      most_wins = child->wins;
  }
  else if(child->games > most_plays && child->wins == most_wins){
    best_i = i;
    most_plays = child->games;
  }
}
board->best_code = root->lst_moves[best_i];
board->best_pos = root->lst_pos[best_i];

clean(root);
---------------------------------------------------------------------------
dup1 = board->dup();
  child = select(root,dup1);

  if(!child->parent){
    printf("Erro arvore!\n");exit(1);
  }

  while(true){
    if(child->parent->parent) child = child->parent;
    else break;
  }

  board->best_code = child->parent->lst_moves[child->id];
  board->best_pos = child->parent->lst_pos[child->id];

  delete(dup1);clean(root);
*/
