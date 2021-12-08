#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <stdexcept>

/* Taken from https://stackoverflow.com/a/25022977 */
std::vector<std::string> split(const std::string& str, int splitLength) {
     int NumSubstrings = str.length() / splitLength;
     std::vector<std::string> ret;
     for (auto i = 0; i < NumSubstrings; i++){
          ret.push_back(str.substr(i * splitLength, splitLength));
     }
     // If there are leftover characters, create a shorter item at the end.
     if (str.length() % splitLength != 0){
          ret.push_back(str.substr(splitLength * NumSubstrings));
     }
     return ret;
}

/* Taken from https://stackoverflow.com/q/16329358 */
std::string remove_spaces(std::string input){
     int length = input.length();
     for (int i = 0; i < length; i++) {
          if(input[i] == ' '){
               input.erase(i, 1);
          }
     }
     return input;
}

/*
     ONLY TO BE CALLED BY THE RUN FUNCTION!!
     a scope used to hold all the functions
*/
class Session{
     public:
          std::map<std::string,int> registers = {
                   {"0010",0}, // rcx
                   {"0011",0}, // rdx
                   {"0012",0}, // r8
                   {"0013",0}, // r9
                   {"0014",0}, // r10
                   {"0015",0}, // r11

          };
          int get_val(std::string &val){
               if (val.at(0) == '0'){
                    if (registers.find(val) == registers.end()){
                         throw std::invalid_argument(std::string("Nonexistent register \"")+val+std::string("\""));
                    } else {
                       return registers[val];
                    }
                    
               } else {
                  std::string n_val = val;
                  n_val[0] = '0'; // 1064 -> 0064
                  n_val.insert(0,std::string("0x")); // 0064 -> 0x0064
                  int ret = std::stoul(n_val,nullptr,16);
                  return ret;
               }
          }
          int mov(std::vector<std::string> &args){
               std::string name = args[0];
               std::string value = args[1]; // is value register
               if (registers.find(name) == registers.end()){
                    throw std::invalid_argument(std::string("Nonexistent register \"")+name+std::string("\""));
               }
               int real_value = get_val(value);
               registers[name] = real_value; // check if register exist, if not error
               return 0;
          }
          int out(std::vector<std::string> args){
               std::string name = args[0];
               int real_name = get_val(name);
               std::cout << real_name;
               return 0;
          }
          int add(std::vector<std::string> args){
               int a = get_val(args[0]);
               int b = get_val(args[1]);
               int v = a+b;
               registers[args[0]] = v;
               return 0;
          }
          int sub(std::vector<std::string> args){
               int a = get_val(args[0]);
               int b = get_val(args[1]);
               int v = a-b;
               registers[args[0]] = v;
               return 0;
          }
};

void run(std::string code){
     Session s;
     std::string code_no_space = remove_spaces(code);
     std::vector<std::string> code_split = split(code_no_space,16); // 15 SOMEHOW MAKES IT WORK !!!!!!!!!
     for(std::string i : code_split){
          std::string t = remove_spaces(i);
          std::vector<std::string> j = split(t,4);
          std::string f = j[0];
          j.erase(j.begin());
          if (f == std::string("0001")){ // MOV A,B
               s.mov(j);
               continue;
          }
          if (f == std::string("0002")){ // OUT
               s.out(j);
               continue;
          }
          if (f == std::string("0003")){ // ADD
               s.add(j);
               continue;
          }
          if (f == std::string("0004")){ // SUB
               s.sub(j);
               continue;
          }
     }
}
