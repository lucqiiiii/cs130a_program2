#ifndef TREE_H
#define TREE_H
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class AVL {
public:
  AVL(){root = NULL; visit = 0; rotate = 0; inserted = 0;}
  ~AVL(){destroy(root);}  
  void insert(int value){root = insert(value,root);}
  void display(){preOrder(root);}
  void reset();
  double getVisit(){return visit;}
  double getRotate(){return rotate;}
  int getInsert(){return inserted;}
  bool lookup(int value){ return lookup(value,root);}
  void printPre(){printPre(root);}
/*  vector<pair<int,int>> printll(){printll(root);}
  vector<pair<int,int>> printlr(){printlr(root);}
  vector<pair<int,int>> printrl(){printrl(root);}
  vector<pair<int,int>> printrr(){printrr(root);} 
*/
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
    return false;
  }

   void printPre(node* root){ 
    if (root == NULL){ 
      cout << "Null" << endl; 
    }
    if(root -> left != NULL || root -> right != NULL){    
      cout << "Node(" << root -> value << ", h=" << root -> height <<"):"         << endl << "  ";
    }
    if(root -> left == NULL && root -> right == NULL){
      cout << "Leaf(" << root -> value << ")" << endl << "  ";
    } 
    printPre(root -> left);  
    printPre(root -> right); 
  }  

/*  vector<pair<int,int>> printll(node* root){
    vector<pair<int,int>> v;
    bool heavy = false;
    checkll(root,heavy,v);
    return v;
  }
  
  void checkll(node* root, bool heavy, vector<pair<int,int>>& v){
    if(root == NULL){
      return v;
    }
    //every time the heavy path goes right, set the min to that root
    if(root -> left -> left == NULL && root -> left -> right == NULL){
      if(root -> right == NULL){//no sibling
        //range is less than the root -> left greater than or equal to 
        //absolute min
      else{//balance with sibling
        //range is less than the root -> left greater than or equal to 
        //absolute min, greater than the root -> left less than the root
      if(heavy == true){
        if(root

    }
    if(height(root -> left) - height(root -> right) == 1){
      heavy = true;
    }
    else if(height(root -> right) - height(root -> left) == 1){
      heavy = false;
    }
    else if(height(root -> left) - height(root -> right) == 0){
      continue;
    }
    checkll(root -> left, heavy, v);
    checkll(root -> right, heavy, v);
  }

  vector<pair<int,int>> printlr(node* root){
  
  }

  vector<pair<int,int>> printrl(node* root){
  
  }

  vector<pair<int,int>> printrr(node* root){
  
  }

*/
};
#endif
