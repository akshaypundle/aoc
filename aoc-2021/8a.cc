#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include "library.h"

using namespace std;
using namespace library;

class Problem {
  public:
    vector<string> lines;
    vector<string> nums;
    void readInput() {
      string line;
      long c=0;

      while(!cin.eof()) {
        getline(cin, line);
        if(!cin.eof()) {
          string digits = line.substr(0,61);
          string number = line.substr(61);
          vector<string> dv = split(digits,' ');
          vector<string> nv = split(number,' ');

          string narr[10]; 
          map<string, int> nmap;
          for(int i=0;i<dv.size();i++) {
            sort(dv[i].begin(), dv[i].end());
            if(dv[i].size() == 2) {nmap[dv[i]]=1;narr[1]=dv[i];}
            if(dv[i].size() == 3) {nmap[dv[i]]=7;narr[7]=dv[i];}
            if(dv[i].size() == 7) {nmap[dv[i]]=8;narr[8]=dv[i];}
            if(dv[i].size() == 4) {nmap[dv[i]]=4;narr[4]=dv[i];}
          }

          for(int i=0;i<dv.size();i++) {
            sort(dv[i].begin(), dv[i].end());
            if(dv[i].size() == 5 && dv[i].find(narr[1][0]) != string::npos && dv[i].find(narr[1][1]) != string::npos ) {nmap[dv[i]]=3;narr[3]=dv[i];}
            if(dv[i].size() == 6 && (dv[i].find(narr[1][0]) == string::npos || dv[i].find(narr[1][1]) == string::npos )) {nmap[dv[i]]=6;narr[6]=dv[i];}
          }

          for(int i=0;i<dv.size();i++) {
            sort(dv[i].begin(), dv[i].end());
            if(dv[i].size() == 6 && 
                dv[i].find(narr[3][0]) != string::npos  &&
                dv[i].find(narr[3][1]) != string::npos  &&
                dv[i].find(narr[3][2]) != string::npos  &&
                dv[i].find(narr[3][3]) != string::npos  &&
                dv[i].find(narr[3][4]) != string::npos 
              ) {nmap[dv[i]]=9;narr[9]=dv[i];}
          }
          for(int i=0;i<dv.size();i++) {
            sort(dv[i].begin(), dv[i].end());
            if(dv[i].size() == 5 && nmap.find(dv[i]) == nmap.end() &&
                narr[9].find(dv[i][0]) != string::npos  &&
                narr[9].find(dv[i][1]) != string::npos  &&
                narr[9].find(dv[i][2]) != string::npos  &&
                narr[9].find(dv[i][3]) != string::npos  &&
                narr[9].find(dv[i][4]) != string::npos 
              ) {nmap[dv[i]]=5;narr[5]=dv[i];}
          }
          for(int i=0;i<dv.size();i++) {
            sort(dv[i].begin(), dv[i].end());
            if(dv[i].size() == 5 && nmap.find(dv[i]) == nmap.end()) {
              narr[2] = dv[i]; nmap[dv[i]]=2;
            } else if(dv[i].size() == 6 && nmap.find(dv[i]) == nmap.end()) {
              narr[0] = dv[i]; nmap[dv[i]]=0;
            } 
          }

          for(int i=0;i<nv.size();i++) {
            sort(nv[i].begin(), nv[i].end());
          }
          c+=nmap[nv[0]]*1000+nmap[nv[1]]*100+nmap[nv[2]]*10+nmap[nv[3]];
          cout << line << " " << nmap[nv[0]]*1000+nmap[nv[1]]*100+nmap[nv[2]]*10+nmap[nv[3]] << "\n";

        }
      }
      cout << c << "\n";
    }

    long solve() {
      /*
      int c=0;
      for(int i=0;i<nums.size();i++) {
        vector<string> out;
        split(nums[i],' ',out);
        for(string w:out) {
          if(w.size() == 2 || w.size() ==3 || w.size() ==4 || w.size() ==7) {
            c++;
          }
        }
      }*/
      return 0;
    }
};

/* 
 * 0 - abcefg  - 6 -> reamining 6 digit one, the leftover is the middle
 * 1 - cf      - 2  -> 2 digit
 * 2 - acdeg   - 5  -> not all contained in 9
 * 3 - acdfg   - 5  -> 5 digit containing 1
 * 4 - bcdf    - 4  -> 4 digit
 * 5 - abdfg   - 5  -> all contained in 9
 * 6 - abdefg  - 6  -> 6 digit not containing 1
 * 7 - acf     - 3  -> 3 digit
 * 8 - abcdefg - 7  -> 7 digit
 * 9 - abcdfg  - 6  -> digits of 3 plus 1 thing
 *
 * */

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
