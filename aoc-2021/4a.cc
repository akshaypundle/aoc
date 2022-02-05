#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Problem {

  public:

    vector<long> calls;
    vector<vector<vector<long>>> boards;

    void split_longs(string &str, char delim, vector<long> &out) {
      size_t start;
      size_t end = 0;
      while ((start = str.find_first_not_of(delim, end)) != string::npos) {
        end = str.find(delim, start);
        out.push_back(stol(str.substr(start, end - start)));
      }
    }

    void readInput() {

      string line;
      getline(cin, line);
      split_longs(line,',',calls);

      while(!cin.eof()) {
        getline(cin, line);
        if(!cin.eof()) boards.push_back(*readBoard());
      }
    }

    void printBoards() {
      for(int t = 0;t<boards.size();t++) {
        for(int i=0;i<5;i++) {
          for(int j=0;j<5;j++) {
            cout << boards[t][i][j] << " ";
          }
          cout << "\n";
        }
        cout << "\n";
      }
    }

    vector<vector<long>> * readBoard() {
      string line;
      vector<vector<long>> *ret = new vector<vector<long>>;

      for(long i=0;i<5;i++) {
        vector<long> *next = new vector<long>;
        getline(cin, line);
        split_longs(line,' ',*next);
        if(next->size() != 5) {
          cout << "fail";
          exit(-1);
        }
        ret->push_back(*next);
      }
      return ret;
    }

    void mark(long n) {
      for(int t = 0;t<boards.size();t++) {
        for(int i=0;i<5;i++) {
          for(int j=0;j<5;j++) {
            if(boards[t][i][j] == n) {
              boards[t][i][j] = -1;
            }
          }
        }
      }
    }

    bool isComplete(const vector<vector<long>>& board) {
      for(int i=0;i<5;i++) {
        bool allm1 = true;
        for(int j=0;j<5;j++) {
          if(board[i][j] != -1) {
            allm1 = false; break;
          }
        }
        if(allm1) return true;
      }

      for(int i=0;i<5;i++) {
        bool allm1 = true;
        for(int j=0;j<5;j++) {
          if(board[j][i] != -1l) {
            allm1 = false; break;
          }
        }
        if(allm1) return true;
      }

      return false;

    }

    long score(const vector<vector<long>> &board, long n) {
      long s=0;
      for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++) {
          if(board[i][j] != -1) s+=board[i][j];
        }
      }
      return s*n;
    }

    long solve() {
      printBoards();
      int numdone = 0;
      bool done[boards.size()] = {false};
      for(long call :calls) {
        mark(call);
        for(int i=0;i<boards.size();i++) {
          vector<vector<long>> board = boards[i];
          if(!done[i] && isComplete(board)) {
            done[i] = true;
            if(numdone == boards.size() - 1) {
              return score(board, call);
            }
            numdone++;
          }
        }
      }
      return -1;
    }

};

int main() {
  Problem p;
  p.readInput();
  cout << p.solve() << "\n";
}
