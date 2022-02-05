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
    int die=1;
    int dierolls=0;
  
    int getDie() {
      int v = die;
      die++;
      dierolls++;
      if(die > 100) die=1;
      return v;
    }

    int getTurn() {
      return getDie()+getDie()+getDie();
    }

    void readInput() {
    }

    int getPos(int p) {
      p = ( (p-1) % 10)+1;
      return p;
    }

    long solve() {
      int p1s=0;
      int p2s=0;
      int p1p = 7;
      int p2p = 4;
      int numturns=0;

      bool p1Turn=true;
      while(p1s < 1000 && p2s < 1000) {
        numturns++;
        if(p1Turn) {
          p1p+=getTurn();
          p1p = getPos(p1p);
          p1s+=p1p;
          p1Turn=false;
        } else {
          p2p+=getTurn();
          p2p = getPos(p2p);
          p2s+=p2p;
          p1Turn=true;
        }
        //cout << p1s << " "<< p2s << "\n";
      }
      cout << min(p1s,p2s)<< " " <<dierolls<<"\n";
      return  min(p1s,p2s)*dierolls;
    }


    // test:
    // 0 -> 10
    // 11 -> 1
    int modit(int i) {
      if(i<= 0) i=i+10;
      if(i>10) i=i-10;
      return (i-1)%10 + 1;
    }

    long solve1() {
      long dp1[31][22][11]; // dp[i][j] = number of ways to make i in j steps ending at pos k
      long dp2[31][22][11]; // dp[i][j] = number of ways to make i in j steps ending at pos k
      for(int i=0;i<31;i++) {
        for(int j=0;j<22;j++) {
          for(int k=0;k<11;k++) {
            dp1[i][j][k]=0;
            dp2[i][j][k]=0;
          }
        }
      }
      dp1[0][0][7]=1;
      dp2[0][0][4]=1;

      long universes[10];
      universes[0]=0;
      universes[1]=0;
      universes[2]=0;
      universes[3]=1;
      universes[4]=3;
      universes[5]=6;
      universes[6]=7;
      universes[7]=6;
      universes[8]=3;
      universes[9]=1;
/*
      for(int j=1;j<22;j++) {
        for(int i=1;i<31;i++) {
          for(int k=1;k<11;k++) {
            for(int dice = 3; dice <= 9; dice++) {
              if(i-k >= 0) {
                dp1[i][j][k] += dp1[i-k][j-1][modit(k-dice)]*universes[dice];
                dp2[i][j][k] += dp2[i-k][j-1][modit(k-dice)]*universes[dice];
              } 
            }
            //if(j<=1 && dp1[i][j][k] >0) cout << " points: "<< i << " iteration
             // "<<j<<" pos:"<<k<<"  universes: "<<dp1[i][j][k] <<"\n";

            //if(j<=2 && dp2[i][j][k] >0) cout << " points: "<< i << " iteration "
            //  <<j<<" pos:"<<k<<"  universes: "<<dp2[i][j][k] <<"\n";
          }
        }
      }

      */
 // dp[i][j][k] = number of ways to make i in j steps ending at pos k

      for(int j=0;j<20;j++) {
        for(int i=0;i<21;i++) {
          for(int k=1;k<11;k++) {
            for(int dice = 3; dice <= 9; dice++) {
              if(i+modit(k+dice) <=30 ) {
                dp1[min(21,i+modit(k+dice))][j+1][modit(k+dice)] += (long) dp1[i][j][k]*universes[dice];
                dp2[min(21,i+modit(k+dice))][j+1][modit(k+dice)] += (long) dp2[i][j][k]*universes[dice];
              }
            }
            //if(j<=1 && dp1[i][j][k] >0) cout << " points: "<< i << " iteration
             // "<<j<<" pos:"<<k<<"  universes: "<<dp1[i][j][k] <<"\n";

            //if(j<=2 && dp2[i][j][k] >0) cout << " points: "<< i << " iteration "
            //  <<j<<" pos:"<<k<<"  universes: "<<dp2[i][j][k] <<"\n";
          }
        }
      }

      long tp1wins=0;
      long tp2wins=0;

      long points1[31][22]; // universes with i points in j steps
      long points2[31][22]; // universes with i points in j steps

      long wins1[22]; // wins at turn i
      long losses1[22]; // 
      long wins2[22]; // wins at turn i
      long losses2[22]; // 


      for(int i=0;i<22;i++) { wins1[i]=0;wins2[i]=0;}
      for(int i=1;i<31;i++) {
        for(int j=1;j<22;j++) {
          long p1=0;
          long p2=0;
          for(int k=1;k<11;k++) {
            p1+=dp1[i][j][k];
            p2+=dp2[i][j][k];
            
            if(i>=21) {
              wins1[j]+=dp1[i][j][k];
              wins2[j]+=dp2[i][j][k];
            } else {
              losses1[j]+=dp1[i][j][k];
              losses2[j]+=dp2[i][j][k];
            }


          }
          points1[i][j]=p1;
          points2[i][j]=p2;
        }
      }
        long w1=0;
        long w2=0;
      for(int t1=1;t1<22;t1++) {
        w1+=wins1[t1]*losses2[t1-1];
        w2+=wins2[t1]*losses1[t1];

          cout << t1 << " "<<w1<<" " <<w2<<"\n";;
      }

      for(int t1=1;t1<22;t1++) {
          long p1loses=0;
          long p1wins=0;
          long p2loses=0;
          long p2wins=0;

          for(int p2=20;p2>=1;p2--) {
            p2loses+=points2[p2][t1-1];
            p1loses+=points1[p2][t1];
          }
          for(int p2=21;p2<31;p2++) {
              p2wins+=points2[p2][t1];
              p1wins+=points1[p2][t1];
          }
          tp1wins+= (p1wins)*p2loses;
          tp2wins+= (p2wins)*p1loses;
          cout << t1 << " "<<tp1wins<<" " <<tp2wins<<"\n";;

      }

      for(int p2=21;p2<31;p2++) {
        for(int t2=1;t2<22;t2++) {
          long p1loses=0;
          for(int p1=20;p1>=0;p1--) {
            p1loses+=points1[p1][t2];
          }
          tp2wins+= points2[p2][t2]*p1loses;
        }
      }
      return tp1wins;
    }
};
int main() {
  Problem p;
  p.readInput();
  cout << p.solve1() << "\n";
}
