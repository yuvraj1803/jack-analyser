//
//  tokenizer.hpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#ifndef tokenizer_hpp
#define tokenizer_hpp

#include <string>
#include <vector>
#include <fstream>
#include "../ref/ref.h"
#include <iostream>

using namespace std;

/*
 
* The tokenizer class processes the input .jack file and breaks it into induvidual tokens.
* This is done by passing the path of the file into the tokenizer() constructor which uses a few internal methods to tokenize the given file.
* There are additional methods builtin which can be viewed as helper functions, which provide an API to interact with the tokenizer.
    Such as:
        tokenizer :: advance()
        tokenizer :: typeOfToken()
        tokenizer :: hasMoreTokens()
 */


class tokenizer{
public:
    
    tokenizer(string file); // constructor
    
    bool hasMoreTokens(); // checks if we have more tokens to process
    void advance(); // advances to the next token
    int tokenType(string token); // returns the type of the token passed    
    vector<string> getAllTokens(); // returns a list of all tokens generated from the input file.
    string getCurrentToken(); // returns the current token pointed by the tokenizer.
    
    int keyword();// return the type of keyword which is the currentToken. returns INVALID if token is not a keyword.
    
private:
    
    vector<string> tokenlist; // list of all tokens
    void filterToken(vector<string> &seperatedTokens, string &token); // tokens might not always be space seperated. this function filters it even further.
    string currentToken;
    int nextTokenPosition = 0;
    
};

#endif /* tokenizer_hpp */
