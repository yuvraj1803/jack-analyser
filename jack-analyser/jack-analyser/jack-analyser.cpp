//
//  jack-analyser.cpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#include "jack-analyser.hpp"

jack_analyser::jack_analyser(string __path){
    
    if(filesystem::is_directory(__path)){ // checks if the path is of a directory
        for(auto file_name : filesystem::directory_iterator(__path)){ // iterates through all the files in the directory and picks the .jack files.
            if(file_name.path().extension() == ".jack") all_files.push_back(file_name.path()); // and adds the .jack files into the all_files vector.
        }
    }else{
        all_files.push_back(__path);
    }
    
    for(auto file : all_files){
        tokenizer * T = new tokenizer(file);
        compilation_engine * CE = new compilation_engine(*T);
        
        T->dumpXML();
        CE->dumpXML(); // dump the generated XML code into a file. this is handled by the compilation engine itself.
        
        // to avoid memory-leaks
        
        free(T);
        free(CE);
    }
    
}
