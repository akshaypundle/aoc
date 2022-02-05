#include <algorithm>
#include <cmath>
#include <iostream>
#include "library.h"
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace library;

class Problem {

  struct Node {
    Node() {
      left = NULL;
      right = NULL;
      val=-999;
    }
    Node *left;
    Node *right;
    int val;
  };

  public:
  Node *parse(string input, int& pos) {
    if(input[pos] == '[') {
      pos++;
      Node *left = parse(input, pos);
      pos++; // for comma
      Node *right = parse(input, pos);
      pos++; // for ]
      Node *ret = new Node();
      ret->left = left;
      ret->right=right;
      return ret;
    } else {
      Node *ret = new Node();
      int n = input[pos++] - '0';
      ret->val=n;
      return ret;
    }
  } 

  string print(Node *root) {
    if(!root) return "";
    if(!root->left || !root->right) {
      return to_string(root->val);
    }
    string l = print(root->left);
    string r = print(root->right);
    return "["+l+","+r+"]";
  }



  Node *add(Node *l , Node *r) {
    Node *res = new Node();
    res->left=l;
    res->right=r;
    return res; 
  }


  Node *reduceTraversePrev;
  Node *reduceTraverseCur;
  Node *reduceTraverseNext;
  bool reduceTraverseFound=false;
  bool reduceTraverseNextFound=false;


  void reduceTraverse(Node *root, int level) {
    bool setReduceFound = false;
    if(!root || reduceTraverseNext) return;
    if(level >= 4 && root->left && root->right && !reduceTraverseCur && !root->left->left && !root->left->right && !root->right->left && !root->right->right) {
      reduceTraverseCur=new Node();
      reduceTraverseCur->left = root->left;
      reduceTraverseCur->right= root->right;
      root->left=NULL;
      root->right=NULL;
      root->val=0;

      setReduceFound = true;
    } else if( (!root->left || !root->right) && !reduceTraverseCur) {
      reduceTraversePrev=root;
    } else if(reduceTraverseFound && !reduceTraverseNextFound && (!root->left || !root->right) ) {
      reduceTraverseNext = root;
      reduceTraverseNextFound = true;
    }

    reduceTraverse(root->left, level+1);
    reduceTraverse(root->right, level+1);
    if(setReduceFound) reduceTraverseFound = true;
  }

  void traverse(Node *root) {
    if(!root) return;
    if(!root->left || !root->right) cout << root->val;
    traverse(root->left);
    traverse(root->right);
  }

  void printReducers() {
    if(reduceTraversePrev) cout << "reduce prev " << reduceTraversePrev->val<<"\n";
    if(reduceTraverseCur) cout << "reduce cur [" << reduceTraverseCur->left->val<<","<<reduceTraverseCur->right->val<<"]\n";
    if(reduceTraverseNext) cout << "reduce next " << reduceTraverseNext->val << "\n";
    cout << "\n";

  }

  void initReduce() {
    reduceTraversePrev=NULL;
    reduceTraverseCur=NULL;
    reduceTraverseNext=NULL;
    reduceTraverseFound=false;
    reduceTraverseNextFound=false;
  }

  void createSplit(Node *root) {
    if(root && root->val >=10) {
      root->left = new Node();
      root->left->val = root->val/2;
      root->right = new Node();
      root->right->val = (root->val+1)/2;
      root->val = -999;
    }
  }

  void reduce(Node *root) {
    initReduce();
    reduceTraverse(root,0);
    printReducers();
    if(reduceTraverseCur) {
      if(reduceTraversePrev) {
        reduceTraversePrev->val+=reduceTraverseCur->left->val;
        if(reduceTraversePrev->val >= 10) {
          //createSplit(reduceTraversePrev);
        }
      }
      if(reduceTraverseNext) {
        reduceTraverseNext->val+=reduceTraverseCur->right->val;
        if(reduceTraverseNext->val >=10) {
          //createSplit(reduceTraverseNext);
        }
      }
    }
  }

  bool splitDone;

  void splitTraverse(Node *root) {
    if(!root || splitDone) return;

    if( (!root->left || !root->right) && !splitDone && root->val >= 10) {
      cout << "splitting  " << root->val<<" " << bool(root->val>=10)<<"\n";
      root->left = new Node();
      root->left->val = root->val/2;
      root->right = new Node();
      root->right->val = (root->val+1)/2;
      root->val = -999;
      splitDone=true;
    }
    splitTraverse(root->left);
    splitTraverse(root->right);
  }

  void split(Node *root) {
    splitDone = false;
    splitTraverse(root);
  }

  void ringum(Node *root) {
    bool reduced = true;
    bool splitted = true;
    while(reduced || splitted) {
        reduce(root);
        cout << print(root) << "\n";
        reduced = !(!reduceTraverseCur);
        if(!reduced) {
          split(root);
          splitted = splitDone;
        }
    }
    cout << "-------------------------- ringum ----------------------\n";
  }

  long magnitude(Node *root) {
    if(!root) return 0;
    if(!root->left || !root->right) return root->val;
    return 3*magnitude(root->left) + 2*magnitude(root->right);

  }

  vector<string> lines;

  void readInput() {
    string line;

    while(!cin.eof()) {
      getline(cin, line);
      if(line.empty()) continue;
      lines.push_back(line);
    }
  }


  void readInput1() {
    string line;

    Node *tot = NULL;
    while(!cin.eof()) {
      getline(cin, line);
      if(line.empty()) continue;
      int pos =0;
      Node * cur = parse(line, pos);
      if(tot == NULL) {
        tot = cur;
      } else {
        tot = add(tot,cur);
      }
      ringum(tot);
      cout << print(tot) << "\n";
    }
    cout << magnitude(tot) << "\n";
  }

  long solve() {
    int max=0;
    for(int i=0;i<lines.size();i++) {
      for(int j=0;j<lines.size();j++) {
        if(i!=j) {
          int pos=0;
          Node *r1= parse(lines[i],pos);
          pos=0;
          Node *r2= parse(lines[j],pos);
          Node *ans = add(r1,r2);
          ringum(ans);
          long mag = magnitude(ans);
          if(mag > max) max=mag;

        }
      }
    }
    return max;
  }


};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
