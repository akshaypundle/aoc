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
    struct machine {
      long registers[4] ={0};
      long inputIndex=0;
      bool fault;
      void reset() {
        for(long i=0;i<4;i++) registers[i]=0;
        inputIndex=0;
        fault=false;
      }

      void print() {
        cout <<"fault "<<fault<< " w:" << registers[0]<<" x:"<<registers[1]<<" y:"<<registers[2]<<" z:"<<registers[3]<<"\n";
      }
    };

    struct instruction {
      string command;
      char reg;
      string val;

      long regIndex() {
        return reg - 'w';
      }

      bool valIsRegister() {
        return val =="w" || val == "x" || val == "y" || val == "z";
      }
      long valAsRegIndex() {
        return val[0]-'w';
      }

      long getValue(machine &m) {
        if(valIsRegister()) {
          return m.registers[valAsRegIndex()];
        } 
        return stoi(val);
      }

      void print() {
        cout << command << " "<<reg<<" "<<val<<"\n";
      }

    };

    vector<instruction> instructions;
    vector<vector<instruction>> programParts;

    instruction parseInstruction(string line) {
      instruction in;
      stringstream ss(line);
      ss >> in.command;
      ss >> in.reg;
      ss >> in.val;
      return in;
    }

    void parse(string line) {
      instructions.push_back(parseInstruction(line));
    }

    void execute(instruction ins,  machine& m, long input[14]) {
      if(m.fault) return;
      if(ins.command == "inp") {
        m.registers[ins.reg - 'w'] = input[m.inputIndex++];
      } else if(ins.command == "add") {
        long va = m.registers[ins.regIndex()];
        long vb = ins.getValue(m);
        m.registers[ins.regIndex()] = va+vb;
      }else if(ins.command == "mul") {
        long va = m.registers[ins.regIndex()];
        long vb = ins.getValue(m);
        m.registers[ins.regIndex()] = va*vb;
      }else if(ins.command == "div") {
        long va = m.registers[ins.regIndex()];
        long vb = ins.getValue(m);
        if(vb == 0) {m.fault=true; return;}
        m.registers[ins.regIndex()] = va/vb;
      }else if(ins.command == "mod") {
        long va = m.registers[ins.regIndex()];
        long vb = ins.getValue(m);
        if(va<0 || vb<=0) { m.fault=true;return;}
        m.registers[ins.regIndex()] = va%vb;
      }else if(ins.command == "eql") {
        long va = m.registers[ins.regIndex()];
        long vb = ins.getValue(m);
        m.registers[ins.regIndex()] = (va==vb ? 1 : 0);
      }
    }

    void calculateProgramParts() {
      long i=-1;
      for(instruction inst : instructions) {
        if(inst.command == "inp") i++;
        if(programParts.size() <= i) programParts.push_back(vector<instruction>());
        programParts[i].push_back(inst);
      }
    }

    void readInput() {
      string line;
      while(!cin.eof()) {
        getline(cin, line);
        if(!line.empty()) parse(line);
      }
      calculateProgramParts();
    }

    bool testInput(long input[14], machine &m, vector<instruction> program, set<long> accept) {
      for(auto in : program) {
        execute(in,m,input);
        if(m.fault) return false;
      }

      return accept.find(m.registers[3]) != accept.end();
    }

    void printOutputsForProgram(long prog) {
      long input[14]={};
      machine m;

      for(long i=1;i<=9;i++) {
        for(long j=0;j<99999;j++) {
          m.reset();
          input[0]=i;
          m.registers[3] = j;

          for(auto in : programParts[prog]) {
            //in.print();
            execute(in,m,input);
            //m.print();
          }
          if(m.registers[3] <=25 && m.registers[3]>=0)
            cout << " program "<< prog<<" input "<<i<<" inp z: "<< j<<" output z:"<<m.registers[3]<<"\n";
        }
      }
    }

    void runInput() {

      machine m;
      long input[14]={5,9,9,9,6,9,1,2,9,8,1,9,3,9};
      m.reset();
      for(auto in:instructions) {
        in.print();
        execute(in,m,input);
        m.print();
      }
      m.print();
    }

    long solve() {

      long input[14]={};
      machine m;

      vector<set<long>> validZ(14);
      validZ[13].insert(0);

      for(long prog=13;prog>=0;prog--) {
        cout << "valid for "<<prog<<": ";
        for(auto xx:validZ[prog]) cout << xx <<", ";
        cout << "\n";
        for(long i=1;i<=9;i++) {
          input[0]=i;
          for(long j=0;j<500000;j++) {
            if(prog == 0 && j > 0) break;
            m.reset();
            m.registers[3] = j;
            if(testInput(input, m, programParts[prog],validZ[prog])) {
              if(prog > 0 ) validZ[prog-1].insert(j);
              cout << "program: " << prog<<" valid input "<< i << " z:"<<j<< " produces z: "<<m.registers[3]<<"\n";
            }
          }
        }
      }


      return 0;
    }

};

int main() {
  Problem p;
  p.readInput();
  p.solve();
}
