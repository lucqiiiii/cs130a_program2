#ifndef TREE_H
#define TREE_H
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class AVL {
public:
  AVL();
  ~AVL(){destroy(root);}  
  void insert(int value){root = insert(value,root);}
  void display(){preOrder(root);}
  void reset();
  double getVisit(){return visit;}
  double getRotate(){return rotate;}
  int getInsert(){return inserted;}
  bool lookup(int value){ return lookup(value,root);}
  void printPre(){int depth = 0; printPre(root,depth);}
  void getInfo(){getInfo(root);}
  vector<pair<int,int>> getLL(){return LL;}
  vector<pair<int,int>> getLR(){return LR;}
  vector<pair<int,int>> getRL(){return RL;}
  vector<pair<int,int>> getRR(){return RR;}

private:
  struct node{
    int value;
    node* left;
    node* right;
    int height;
  };

  node* newnode(int value){
    node* n = new node();
    n -> value = value;
    n -> left = NULL;
    n -> right = NULL;
    n -> height = 1;
    return n;
  }

  node* root;
  double visit;
  double rotate;
  int inserted;
  vector<pair<int,int>> LL;
  vector<pair<int,int>> LR;
  vector<pair<int,int>> RL;
  vector<pair<int,int>> RR;

  void destroy(node* root){
    if(root != NULL){
      destroy(root -> left);
      destroy(root -> right);
      delete root;
    }
  }
  
  int height(node* n){
    return n == NULL ? 0 : n -> height;
  }

  int max(int a, int b){
    return (a > b)? a : b;
  }

  node* insert(int value, node* root){
    if(root == NULL){
      inserted++;
      return newnode(value);
    }
    else if(value < root -> value){
      root -> left = insert(value,root -> left);
      visit++;
    }
    else if(value > root -> value){
      root -> right = insert(value, root -> right);
      visit++;
    }
    else{
      visit++;
      return root;
    }
    root -> height = max(height(root -> left), height(root -> right)) + 1;
   
    return balance(root);
  }

  node* balance(node* root){
    if(root == NULL)
      return root;
    if(height(root -> left) - height(root -> right) > 1){
      if(height(root -> left -> left) >= height(root -> left -> right)){
        rotate++;
        return singleleft(root);        
      }
      else{
        rotate += 2;
        return doubleleft(root);
      }
    }
    else if(height(root -> right) - height(root -> left) > 1){
      if(height(root -> right -> right) >= height(root -> right -> left)){
        rotate++;
        return singleright(root);
      }
      else{
        rotate += 2;
        return doubleright(root);
      }
    }
    return root;
  } 
    
  node* singleleft(node* root){
    node* temp = root -> left;
    root -> left = temp -> right;
    temp -> right = root;
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    temp -> height = max(height(temp -> left), root -> height) + 1;
    return temp;
  }

  node* singleright(node* root){
    node* temp = root -> right;
    root -> right = temp -> left;
    temp -> left = root;
    root -> height = max(height(root -> right), height(root -> left)) + 1;
    temp -> height = max(height(temp -> right), root -> height) + 1;
    return temp;
  }

  node* doubleleft(node* root){
    root -> left = singleright(root -> left);
    return singleleft(root);
  }
  
  node* doubleright(node* root){
    root -> right = singleleft(root -> right);
    return singleright(root);
  }

  void preOrder(node* root){
    if(root != NULL)  
      {  
        std::cout << root -> value << " ";  
        preOrder(root -> left);  
        preOrder(root -> right);  
      }
  }
  
  bool lookup(int value, node* root){
    if(root == NULL){
      return false;
    }
    else if(root -> value == value){
      visit++;
      return true;
    }
    else if(root -> value < value){
      visit++;
      return lookup(value, root -> right);
    }
    else if(root -> value > value){
      visit++;
      return lookup(value, root -> left);
    }
    return false;
  }

   void printPre(node* root, int depth){ 
    if (root == NULL){ 
      for(int i = 0; i < depth; i++){
        cout << "  ";
      } 
      cout << "Null" << endl; 
    }
    else if(root -> left != NULL || root -> right != NULL){   
      for(int i = 0; i < depth; i++){
        cout << "  ";
      } 
      cout << "Node(" << root -> value << ", h=" << (root -> height) - 1          <<"):" << endl;
      depth++;
      printPre(root -> left,depth);  
      printPre(root -> right,depth); 

    }
    else if(root -> left == NULL && root -> right == NULL){
      for(int i = 0; i < depth; i++){
        cout << "  ";
      } 
      cout << "Leaf(" << root -> value << ")" << endl;
      return;
    } 
    else{
      return;
    }
  }  

  void getInfo(node* root){
    if(root == NULL){
      return;
    }
    int min = -2147483648;
    int max = 2147483647;
    int f1 = 0;
    int f2 = 0;
    check(root,min,max,f1,f2);
  }

  void insertHelper(std::vector<std::pair<int,int> >& v, int min, int max) {
    if(min <= max) v.push_back(std::pair<int,int>(min, max));
  }
  
  void check(node* root, int min, int max, int f1, int f2){
    if(root == NULL){
      return;
    }
    int direction = height(root -> left) - height(root -> right);
    if(direction == 1){//left taller
      check(root -> left, min, root -> value - 1, -1, 0);
      check(root -> right, root -> value + 1, max, 0, 0);
    }
    else if(direction == -1){//left shorter
      check(root -> left, min, root -> value - 1, 0, 0);
      check(root -> right, root -> value + 1, max, 1, 0);
    }
    else{//equal height
      if(f2 == 0){
        check(root -> left, min, root -> value - 1, f1, -1);
        check(root -> right, root -> value + 1, max, f1, 1);
      }
      else{
        check(root -> left, min, root -> value - 1, f1, f2);
        check(root -> right, root -> value + 1, max, f1, f2);
      }
    }

    if(root -> left == NULL && root -> right == NULL){//leaf
//      std::cout << "I'm at " << root->value << std::endl;
      if(f1 == -1){//f1 is set to left, the first op is left
        if(f2 == -1){//left with sibling
	    insertHelper(LL,min,root -> value - 1);
	    insertHelper(LL,root -> value + 1, max);
        }
        else if(f2 == 1){//left with sibling
	    insertHelper(LR,root -> value + 1, max);
	    insertHelper(LR,min, root -> value - 1);
        }
        else{//no sibling
            insertHelper(LL,min,root -> value - 1);
  	    insertHelper(LR,root -> value + 1,max);
        }
      }
      else if(f1 == 1){//f1 set to right, the first op is right
        if(f2 == -1){//left with sibling
            insertHelper(RL,min,root -> value - 1);
	    insertHelper(RL,root -> value + 1, max);
        }
        else if(f2 == 1){//left with sibling
	    insertHelper(RR,root -> value + 1,max);
      	    insertHelper(RR,min, root -> value - 1);
        }
        else{//no sibling
            insertHelper(RL,min,root -> value - 1);
	    insertHelper(RR,root -> value + 1,max);
        }
      }
      else{//f1 not set, no rotation
        return;
      }
    }
  }
  
};
#endif
