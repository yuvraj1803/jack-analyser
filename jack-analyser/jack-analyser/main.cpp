//
//  main.cpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#include <iostream>
#include "../tokenizer/tokenizer.hpp"
#include "../compilation-engine/compilation-engine.hpp"
#include "jack-analyser.hpp"

int main(int argc, const char * argv[]) {
    
    string filename = "/Users/boju/Desktop/nand2tetris/jack-analyser/jack-analyser/jack-analyser/file.jack";

    tokenizer tok = *new tokenizer(filename);
    compilation_engine com = *new compilation_engine(tok);
    
    for(auto i: com.getXMLContent()){
        cout << i << '\n';
    }
    
    
    return 0;
}
