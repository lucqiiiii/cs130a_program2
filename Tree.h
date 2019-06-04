#ifndef TREE_H
#define TREE_H
#include <cstddef>
#include <iostream>
class AVL {
public:
  AVL(){root = NULL; visit = 0; rotate = 0; insert = 0;}
  ~AVL(){destroy(root);}  
  void insert(int value){root = insert(value,root);}
  void display(){preOrder(root);}
  void reset();
  double getVisit(){return visit;}
  double getRotate(){return rotate;}
  int getInsert(){return insert;}
  bool lookup(int value){lookup(value,root)};
  void printPre(){printPre(root);}
  void printll(){printll(root);}
  void printlr(){printlr(root);}
  void printrl(){printrl(root);}
  void printrr(){printrr(root);} 

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
  int insert;
  
  destroy(node* root){
    while(root != NULL){
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
    if(root == NULL)
      return newnode(value);
      insert++;
    else if(value < root -> value){
      root -> left = insert(value,root -> left);
      visit++;
    }
    else if(value > root -> value){
      root -> right = insert(value, root -> right);
      visit++;
    }
    else{
      return this;
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
    if(root -> value == value){
      return true;
    }
    else if(root -> value < value){
      lookup(value, root -> right);
      visit++;
    }
    else if(root -> value > value){
      lookup(value, root -> left);
      visit++;
    }
  }

   void printPre(node* root){ 
    if (root == NULL){ 
      cout << "Null" << endl; 
    }
    if(root -> left != NULL | root -> right != NULL){    
      cout << "Node(" << root -> value << ", h=" << root -> height <<"):"         << endl << "  ";
    }
    if(root -> left == NULL && root -> right == NULL){
      cout << "Leaf(" << root -> value << ")" << endl << "  ";
    } 
    printPre(root -> left);  
    printPre(root -> right); 
  }  

  void printll(node* root){
    cout << "The following inserts would cause a left-left rotation: "          << endl;
  }

  void printlr(node* root){
  
  }

  void printrl(node* root){
  
  }

  void printrr(node* root){
  
  }


};
#endif
