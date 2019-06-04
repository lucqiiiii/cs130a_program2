#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

int main(){
/*  AVL t;
  t.insert(10);
  t.insert(20);
  t.insert(30);
  t.insert(40);
  t.insert(50);
  t.insert(25);
  t.display();
  cout << "\n";  
*/
  if(argc != 2){
    std::cerr << "Something is wrong" << endl;
    exit(1);
  }

  std::ifstream check(testfile);
  if(check.fail()) {
    std::cerr << "Unable to open file: " << testfile << '\n';
    exit(1);
  }

  AVL t;

  while(std::getline(check, line)){
    std::istringstream iss(line);
    string word;
    iss >> word;
    int value;

    if(word == "insert"){
      int count = 0;
      int length = 0;
      t.reset();
      while(iss >> value){
        length++；
        t.insert(value);       
      }
      count = t.getInsert();
      std::cout << "Added " << count << " of " << length << " nodes.\n"
      std::cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations." << endl;
    }

    else if(word == "lookup"){
      int length = 0;
      int count = 0;
      std::vector<int> v;
      t.reset();
      while(iss >> value){
        length++;
        if(t.lookup(value) == true){
          count++;
          v.std::push_back(value);
        }
      }
      std::cout << "Found " << count << " of " << length << " nodes:" << v
      << endl;
      std::cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations." << endl;
    }
    
    else if(word == "print"){
      word = iss >> word;
      if(word == "tree"){
        printPre();
      }
      else if(word == "left-left"){
        printll();
      }
      else if(word == "left-right"){
        printlr();
      }
      else if(word == "right-left"){
        printrl();
      }
      else if(word == "right-right"){
        printrr();
      }
    }
  }
}
