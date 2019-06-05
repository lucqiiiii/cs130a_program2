#include "Tree.h"
#include <vector>

AVL::AVL(): LL(), LR(), RL(), RR(){
  root = NULL; 
  visit = 0; 
  rotate = 0; 
  inserted = 0;
}

void AVL::reset(){
  visit = 0;
  rotate = 0;
  inserted = 0;
  LL.clear();
  LR.clear();
  RL.clear();
  RR.clear();
}



