#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include "runner.hpp"

/* Taken from https://stackoverflow.com/a/16410748 */
std::string load_bin(std::string &fname){
    unsigned char x;
    std::ifstream input(fname,std::ios::binary);
    input >> std::noskipws;
    std::ostringstream oss;
    while (input >> x){
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)x;
    }
    std::string fstr = oss.str();
    return fstr;
}
int main(int argc,char *argv[]){
    std::string fname = argv[1];
    std::string bin_data = load_bin(fname);
    run(bin_data);
    return 0;
}