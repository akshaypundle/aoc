#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

int main() {
  long d=0;
  long h=0;
  long aim=0;

  string command;
  long val;
  while(!cin.eof()) {
    cin >> command;
    if(cin.eof()) break;
    cin >> val;
    if(command == "forward") {
      h+= val;
      d+=(aim*val);
    } else if(command == "down") {
      aim+=val;
    } else if(command == "up") {
      aim-=val;
    }

    cout << d << " "<<h<<" "<<d * h<<"\n";
  }
  cout << d * h<<"\n";
}
