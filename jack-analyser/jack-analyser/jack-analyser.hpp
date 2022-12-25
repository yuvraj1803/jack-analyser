//
//  jack-analyser.hpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#ifndef jack_analyser_hpp
#define jack_analyser_hpp

#include <string>
#include <fstream>
#include <filesystem>

#include "../tokenizer/tokenizer.hpp";
#include "../compilation-engine/compilation-engine.hpp"

using namespace std;


/*
 
 The jack_analyser class utilises the tokenizer and the compilation engine to generate the corresponding XML code for the provided jack file.
 
 If the input path is of a directory, we create an XML file for each of the .jack files.
 
 */

class jack_analyser{
    
public:
    
    jack_analyser(string path);
    
private:
    
    vector<string> all_files; // this stores all the .jack files present in the input path.
    
};

#endif /* jack_analyser_hpp */
