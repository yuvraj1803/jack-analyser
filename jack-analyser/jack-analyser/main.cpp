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
        
    if(argc < 2){
        cout << "very few arguments." << '\n';
        cout << "try passing the filename after the executable" << '\n';
        exit(1);
    }
    
    string path = argv[1];

    jack_analyser * JA = new jack_analyser(path);
    
    free(JA);
    
    return 0;
}
