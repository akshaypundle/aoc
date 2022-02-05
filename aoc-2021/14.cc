#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <sstream>
#include "library.h"

using namespace std;
using namespace library;

class Problem {
  public:
    string start;
    map<string,char> transform;
    void readInput() {
      getline(cin, start);

      string line;
      while(!cin.eof()) {
        getline(cin, line);
        if(line.size() == 0 ) continue;
        stringstream ss(line);
        string l;
        char a,b;
        string r;
        ss >> l >> a>>b>>r;
        cout << l << "-> " << r[0] << "\n";
        transform[l]=r[0];
      }
    }

    string makeStr(char c1, char c2) {
        stringstream ss;
        ss << c1 << c2;
        return ss.str();
    }


    long solve1() {
      map<string, long> count;
      for(int i=0;i<start.size()-1;i++) {
        string s = makeStr(start[i],start[i+1]);
        if(count.find(s) == count.end()) count[s]=1;
        else count[s]++;
      }
      for(int time = 0; time < 40;time++) {
        map<string, long> tmpcount;
        for(auto it = count.begin();it!=count.end();it++) {
          if(transform.find(it->first) != transform.end()) {
            string new1=makeStr(it->first[0],transform[it->first]);
            string new2=makeStr(transform[it->first], it->first[1]);
            if(tmpcount.find(new1) == tmpcount.end()) tmpcount[new1]=it->second;
            else tmpcount[new1]+=it->second;

            if(tmpcount.find(new2) == tmpcount.end()) tmpcount[new2]=it->second;
            else tmpcount[new2]+=it->second;

          }
        }
        /*
        for(auto it=tmpcount.begin();it!=tmpcount.end();it++) {
          if(count.find(it->first) != count.end()) {
            count[it->first]+=tmpcount[it->first];
          } else {
            count[it->first]=tmpcount[it->first];
          }
        }*/
        count = tmpcount;
      }
      long freq[26] = {0};

      for(auto it=count.begin();it!=count.end();it++) {
        freq[it->first[0]-'A']+=it->second;
        //freq[it->first[1]-'A']+=it->second;
      }

      freq[start[start.size()-1]-'A']++;

      long mm=0, mn=999999999999999999;
      char minc, maxc;
      for(int i=0;i<26;i++) {
        if(freq[i]<mn && freq[i]>0) {minc='A'+i;mn = freq[i];}
        if(freq[i] > mm) {maxc='A'+i;mm = freq[i];}
      }

      cout << time<<"    "<<minc<<":"<<mn<<" " <<maxc<<":"<<mm<< "    diff:"<<mm-mn<<"\n";
      return 0;
    }

    long solve() {
      string news = start;
      for(int time = 0; time < 40;time++) {
        string newer="";
        for(int i=0;i<news.size()-1;i++) {
          stringstream ss;
          ss << news[i] << news[i+1];
          string s = ss.str();
          if(transform.find(s) != transform.end()) {
            newer+=news[i];
            newer+=transform[s];
          } else {
            newer+=news[i];
          }
        }
        newer+=news[news.size()-1];
        news = newer;
        cout << news << "\n\n";

        int freq[26] = {0};
        for(int i=0;i<news.size();i++) {
          freq[news[i]-'A']++;
        }
        int mm=0, mn=999999999;
        char minc, maxc;
        for(int i=0;i<26;i++) {
          if(freq[i]<mn && freq[i]>0) {minc='A'+i;mn = freq[i];}
          if(freq[i] > mm) {maxc='A'+i;mm = freq[i];}
        }

        cout << time<<"    "<<minc<<":"<<mn<<" " <<maxc<<":"<<mm<<"\n";
      }
      return 0;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve1() << "\n";
}
