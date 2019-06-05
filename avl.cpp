#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){
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
    cerr << "Something is wrong" << endl;
    exit(1);
  }

  std::ifstream check(argv[1]);
  if(check.fail()) {
    cerr << "Unable to open file: " << argv[1] << '\n';
    exit(1);
  }

  AVL t;
  string line;
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
        length++;
        t.insert(value);       
      }
      count = t.getInsert();
      cout << "Added " << count << " of " << length << " nodes.\n";
      cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations.\n" << endl;
    }

    else if(word == "lookup"){
      int length = 0;
      int count = 0;
      unsigned int i;
      vector<int> v;
      t.reset();
      while(iss >> value){
        length++;
        if(t.lookup(value) == true){
          count++;
          v.push_back(value);
        }
      }
      cout << "Found " << count << " of " << length << " nodes: [";
      for(i = 0; i < v.size()-1; i++){
        cout << v[i] << ", ";
      }
      cout << v[i]<< "]" << endl;
      cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations." << endl;
    }
    
    else if(word == "print"){
      iss >> word;
      if(word == "tree"){
        t.printPre();
      }
/*      else if(word == "left-left"){
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
      }*/
    }
  }
}
