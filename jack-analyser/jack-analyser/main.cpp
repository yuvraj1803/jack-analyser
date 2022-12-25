//
//  main.cpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#include <iostream>
#include "../tokenizer/tokenizer.hpp"
#include "jack-analyser.hpp"

int main(int argc, const char * argv[]) {
    
    string filename = "/Users/boju/Desktop/nand2tetris/jack-analyser/jack-analyser/jack-analyser/file.jack";

    tokenizer tok = *new tokenizer(filename);
    
    for(auto token : tok.getAllTokens()){
        cout << token << '\n';
    }
    
    return 0;
}
