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
  public:
    long totalver;
    int pos;
    string input;

    void readInput() {
      string line;
      getline(cin, line);

      for(int i=0;i<line.size();i++) {
        if( line[i]=='0' ) input += "0000";
        if( line[i]=='1' ) input += "0001";
        if( line[i]=='2' ) input += "0010";
        if( line[i]=='3' ) input += "0011";
        if( line[i]=='4' ) input += "0100";
        if( line[i]=='5' ) input += "0101";
        if( line[i]=='6' ) input += "0110";
        if( line[i]=='7' ) input += "0111";
        if( line[i]=='8' ) input += "1000";
        if( line[i]=='9' ) input += "1001";
        if( line[i]=='A' ) input += "1010";
        if( line[i]=='B' ) input += "1011";
        if( line[i]=='C' ) input += "1100";
        if( line[i]=='D' ) input += "1101";
        if( line[i]=='E' ) input += "1110";
        if( line[i]=='F' ) input += "1111";
      }
      pos=0;
      totalver=0;
    }
    int bitsToInt(string bits) {
      int ret=0;
      for(int i=0;i<bits.size();i++) {
        ret*=2;
        if(bits[i] == '1') ret+=1;
      }
      return ret;
    }

    string getBitsAsString(int n) {
      string ret = input.substr(pos, n);
      pos+=n;
      return ret;
    }

    int getBitsAsInt(int n) {
      return bitsToInt(getBitsAsString(n));
    }

    long getPacketValue(vector<long> packets, int type) {

      if(type == 0) {
        long s = 0;
        for(int i=0;i<packets.size();i++) s+=packets[i];
        return s;
      } else if(type == 1) {
        long p = 1;
        for(int i=0;i<packets.size();i++) p*=packets[i];
        return p;
      } else if(type == 2) {
        long minp = packets[0];
        for(int i=0;i<packets.size();i++) if(packets[i] < minp) minp=packets[i];
        return minp;
      } else if(type == 3) {
        long maxp= packets[0];
        for(int i=0;i<packets.size();i++) if(packets[i] > maxp) maxp=packets[i];
        return maxp;
      } else if(type == 5) {
        if(packets[0] > packets[1]) return 1;
        else return 0;
      } else if(type == 6) {
        if(packets[0] < packets[1]) return 1;
        else return 0;
      } else if(type == 7) {
        if(packets[0] == packets[1]) return 1;
        else return 0;
      }
      return 0;
    }

    long parsePacket() {
      int ver = getBitsAsInt(3);
      totalver+=ver;
      int type = getBitsAsInt(3);

      if(type == 4) {
        long num = 0;
        string nextbits;
        do {
          nextbits=getBitsAsString(5);
          num*=16;
          num+=bitsToInt(nextbits.substr(1));
        } while(nextbits[0] == '1');
        return num;
      } else {
        vector<long> vals;
        if(getBitsAsString(1)[0] == '0') {
          // next 15 bits are total length
          int length=getBitsAsInt(15);
          int curpos=pos;


          while(pos < curpos+length) {
            vals.push_back(parsePacket());
          }
        } else {
          // next 11 bits is number of subpackets
          int npackets=getBitsAsInt(11);
          for(int i=0;i<npackets;i++) {
            vals.push_back(parsePacket());
          }
        }
        return getPacketValue(vals, type);
      }
      return 0;
    }

    long solve() {
      long v=0;
      while(input.size() - pos > 6) {
        v+=parsePacket();
      }
      return v;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
