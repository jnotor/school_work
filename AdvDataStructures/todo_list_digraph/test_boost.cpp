#include <vector>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

std::vector<int> split(const std::string& s, char delimiter) {
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        std::stringstream geek(token);
        int x;
        geek >> x;
        tokens.push_back(x);
    }
   return tokens;
}

int main() {
    std::vector <int> vec;
    std::cout << vec.at(10) << std::endl;
    return 0;
}