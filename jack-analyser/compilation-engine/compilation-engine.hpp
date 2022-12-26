//
//  compilation-engine.hpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#ifndef compilation_engine_hpp
#define compilation_engine_hpp

#include "../tokenizer/tokenizer.hpp"
#include <fstream>


/*
  The compilation_engine class utilises the services of the tokenizer class.
    We generate an XML file with reference to the Jack Grammar after processing the tokens one by one.
    
    This is done recursively. keep in mind, this is an LL grammar. LL(1) in almost all cases. LL(2) when dealing with expressions.
    
    For each rule in the Jack Grammar,
        X -> YZ...
        we recursively process as follows:
            compileX(){
                <X>
                    compileY();
                    compileZ();
                </X>
            }
    
 */

class compilation_engine{
    
public:
    
    compilation_engine(tokenizer T); // constructor
    void dumpXML(); // dumps the processed XML into a .xml file
    vector<string> getXMLContent();
    
private:
    
    tokenizer * tok; // pointer to the tokenizer that has processed the current file.
    string filename; // the current file being processed.
    void compilation_engine_begin(); // starts generating XML code for the processed tokens.
    vector<string> XMLContent; // holds the content that will be dumped into the XML file at the end. The 'int' part of the pair contains the level of indentation.
    int indentLevel = 0; // keeps track of the level of indentation of current markup to be generated in the XML file.
    
    
    // the grammar related to the methods below are stated beside their declarations in the .cpp file.
    
    inline void addCurrentToken(); // this will add the current token's markup into the XMLContent vector.
    
    void compileClass();
    void compileClassVarDec();
    void compileSubroutineDec();
    void compileType();
    void compileParameterList();
    void compileSubroutineBody();
    void compileVarDec();
    void compileStatements();
    void compileStatement();
    void compileWhile();
    void compileLet();
    void compileReturn();
    void compileDo();
    void compileIf();
    void compileExpression();
    void compileTerm();
    void compileSubroutineCall();
    void compileExpressionList();
    
};


#endif /* compilation_engine_hpp */
