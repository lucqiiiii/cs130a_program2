#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){

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
    istringstream iss(line);
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
      if(v.size() == 0){
       cout << "]" << endl;
       cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations.\n" << endl;
      }
      else{
        for(i = 0; i < v.size()-1; i++){
          cout << v[i] << ", ";
        }
        cout << v[i]<< "]" << endl;
        cout << "Visited " << t.getVisit() << " (" << (t.getVisit()/length) << ") nodes and performed " << t.getRotate() << " (" << (t.getRotate()/length) << ") rotations.\n" << endl;
      }
    }
 
    else if(word == "print"){
      iss >> word;
      t.reset();
      t.getInfo();
      if(word == "tree"){
        t.printPre();
        cout << endl;
      }
      else if(word == "left-left"){
        vector<pair<int,int>> v = t.getLL();
        if(v.size() == 0){
          cout << "No inserts would cause a left-left rotation." << endl << endl;
        }
        else{
          size_t i; 
          cout << "The following inserts would cause a left-left rotation:" << endl;
          for(i = 0; i < v.size() - 1; i++){
            if(v[i].second != v[i].first)
              cout << v[i].first << " to " << v[i].second << ", ";
            else
              cout << v[i].first << ", ";
          }
          if(v[i].second != v[i].first)
            cout << v[i].first << " to " << v[i].second << endl << endl;
          else
            cout << v[i].first << endl << endl;
        }
      }
      else if(word == "left-right"){
        vector<pair<int,int>> v = t.getLR();
        if(v.size() == 0){
          cout << "No inserts would cause a left-right rotation." << endl << endl;
        }
        else{
          size_t i; 
          cout << "The following inserts would cause a left-right rotation:" << endl;
          for(i = 0; i < v.size() - 1; i++){
            if(v[i].second != v[i].first)
              cout << v[i].first << " to " << v[i].second << ", ";
            else
              cout << v[i].first << ", ";
          }
          if(v[i].second != v[i].first)
            cout << v[i].first << " to " << v[i].second << endl << endl;
          else
            cout << v[i].first << endl << endl;
        }
      }
      else if(word == "right-left"){
        vector<pair<int,int>> v = t.getRL();
        if(v.size() == 0){
          cout << "No inserts would cause a right-left rotation." << endl << endl;
        }
        else{
          size_t i; 
          cout << "The following inserts would cause a right-left rotation:" << endl;
          for(i = 0; i < v.size() - 1; i++){
            if(v[i].first != v[i].second)
              cout << v[i].first << " to " << v[i].second << ", ";
            else
              cout << v[i].first << ", ";
          }
          if(v[i].first != v[i].second)
            cout << v[i].first << " to " << v[i].second << endl << endl;
          else
            cout << v[i].first << endl << endl;
        }
      }
      else if(word == "right-right"){
        vector<pair<int,int>> v = t.getRR();
        if(v.size() == 0){
          cout << "No inserts would cause a right-right rotation." << endl << endl;
        }
        else{
          size_t i; 
          cout << "The following inserts would cause a right-right rotation:" << endl;
          for(i = 0; i < v.size() - 1; i++){
            if(v[i].first != v[i].second)
              cout << v[i].first << " to " << v[i].second << ", ";
            else
              cout << v[i].first << ", ";
          }
          if(v[i].first != v[i].second)
            cout << v[i].first << " to " << v[i].second << endl << endl;
          else
            cout << v[i].first << endl << endl;
        }
      }
    }
  }
}
