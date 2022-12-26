//
//  compilation-engine.cpp
//  jack-analyser
//
//  Created by Yuvraj Sakshith on 25/12/22.
//

#include "compilation-engine.hpp"


// the corresponding grammar rules are written adjacent to the compilexxx functions.

compilation_engine::compilation_engine(tokenizer T){
    filename = T.getCurrentFilename();
    tok = &T;
    compilation_engine_begin();
}

void compilation_engine::dumpXML(){
    
    // remove .jack from the filename;
    
    string outputFile = "";
    for(auto c: filename){
        if(c == '.') break;
        outputFile += c;
    }
    outputFile += ".xml";
    ofstream outputFileStream(outputFile);
    for(auto line : XMLContent){
        outputFileStream << line << '\n';
    }
    
    outputFileStream.close();
    
}

inline void compilation_engine::addCurrentToken(){
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
}

vector<string> compilation_engine::getXMLContent(){
    return XMLContent;
}

void compilation_engine::compilation_engine_begin(){
    
    // we assume that all .jack files start with a class declaration.
    // hence, its enough to just process class declarations.
    // imagine 'class' to be at the top of the parse tree.
    
    while(tok->hasMoreTokens()){
        if(tok->getCurrentToken() == "class"){
            compileClass();
        }
        tok->advance();
    }
    
}

void compilation_engine::compileClass(){ //class : 'class' className { classVarDec*, subroutineDec* }
    XMLContent.push_back("<class>");
    
    
    // 'class'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // className
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    string className = tok->getCurrentToken();
    tok->advance();
    
    
    // {
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    // classVarDec*
    while(tok->getCurrentToken() == "field" or tok->getCurrentToken() == "static") compileClassVarDec();
    // subroutineDec*
    while(tok->getCurrentToken() == "constructor" or tok->getCurrentToken() == "function" or tok->getCurrentToken() == "method") compileSubroutineDec();
    
    // '}'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    XMLContent.push_back("</class>");
}

void compilation_engine::compileClassVarDec(){ // ('static | 'field') type varName (','varName)* ';'
    
    XMLContent.push_back("<classVarDec>");
    
    // ('static' | 'field')
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // type
    compileType();
    
    //varName
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // (',' varName)*
    while(tok->hasMoreTokens() and tok->getCurrentToken() != ";"){
        // ','
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // varName
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }
        
    // ';'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    XMLContent.push_back("</classVarDec>");
    
}

void compilation_engine::compileType(){
    
    // 'int' | 'char' | 'boolean' | className
    
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
}

void compilation_engine::compileSubroutineDec(){ // ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
    
    XMLContent.push_back("<subroutineDec>");
    
    // constructor | function | method
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    // ('void' | type)
    if(tok->getCurrentToken() == "void"){
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }else{
        compileType();
    }
    
    // subroutineName
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    // '('
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // parameterList
    compileParameterList();
    
    
    // ')'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // subroutineBody
    compileSubroutineBody();
    
    
    XMLContent.push_back("</subroutineDec>");
    
}

void compilation_engine::compileSubroutineBody(){ // '{' varDec* statements '}'
    
    XMLContent.push_back("<subroutineBody>");
    
    // '{'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // varDec*
    
    while(tok->getCurrentToken() == "var") compileVarDec();
    
    // statements
    compileStatements();
    
    // '}'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    XMLContent.push_back("</subroutineBody>");
    
}

void compilation_engine::compileVarDec(){ // 'var' type varName (',', varName)*';'
    
    XMLContent.push_back("<varDec>");
    
    // 'var'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // type
    compileType();
    
    // varName
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
        // (',' varName)*
    while(tok->getCurrentToken() != ";"){
        // ','
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // varName
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }
    
    // ';'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    XMLContent.push_back("</varDec>");
    
    
}

void compilation_engine::compileStatements(){ // statement*
    
    XMLContent.push_back("<statements>");
    
    // statement*
    while(tok->getCurrentToken() == "if" or tok->getCurrentToken() == "let" or tok->getCurrentToken() == "do" or tok->getCurrentToken() == "return" or tok->getCurrentToken() == "while"){
        compileStatement();
    }
    
    XMLContent.push_back("</statements>");
    
}

void compilation_engine::compileStatement(){ // if | while | let | do | return
    
    
    if(tok->getCurrentToken() == "if") compileIf();
    if(tok->getCurrentToken() == "while") compileWhile();
    if(tok->getCurrentToken() == "let") compileLet();
    if(tok->getCurrentToken() == "do") compileDo();
    if(tok->getCurrentToken() == "return") compileReturn();
}

void compilation_engine::compileIf(){ // 'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}')?
    
    XMLContent.push_back("<ifStatement>");
    
    // 'if'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // '('
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // expression
    compileExpression();
    
    // ')'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // '{'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // statements
    compileStatements();
    
    // '}'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    // (else '{' statements '}')?
    if(tok->getCurrentToken() == "else"){
        // else
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // '{'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // statements
        compileStatements();
        
        // '}'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }
    
    
    XMLContent.push_back("</ifStatement>");
    
}

void compilation_engine::compileWhile(){ // 'while' '(' expression ')' '{' statements '}'
    
    XMLContent.push_back("<whileStatement>");
    
    // while
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // '('
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // expression
    compileExpression();
    
    // ')'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // '{'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // statements
    compileStatements();
    
    // '}'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    XMLContent.push_back("</whileStatement>");
    
}

void compilation_engine::compileLet(){ // 'let' varName ('[' expression ']')? '=' expression ';'
    
    XMLContent.push_back("<letStatement>");
    
    // let
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // varName
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // ('[' expression ']')?
    if(tok->getCurrentToken() == "["){
        // '['
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // expression
        compileExpression();
        
        // ']'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }
    
    // '='
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // expression
    compileExpression();
    
    // ';'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    XMLContent.push_back("</letStatement>");

    
}

void compilation_engine::compileDo(){ // do subroutineCall ';'
    
    XMLContent.push_back("<doStatement>");
    
    // do
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // subroutineCall
    compileSubroutineCall();
    
    // ';'
    
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    XMLContent.push_back("</doStatement>");
    
}

void compilation_engine::compileReturn(){ // return expression?';'
    
    XMLContent.push_back("<returnStatement>");
    
    // return
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    // expression?
    if(tok->getCurrentToken() != ";"){
        compileExpression();
    }
    
    // ';'
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    XMLContent.push_back("</returnStatement>");
    
}

void compilation_engine::compileExpression(){ // term (op term)*
    
    XMLContent.push_back("<expression>");
    
    // term
    compileTerm();
    
    // (op term)*
    while(   tok->getCurrentToken() == "+"
          or tok->getCurrentToken() == "-"
          or tok->getCurrentToken() == "*"
          or tok->getCurrentToken() == "/"
          or tok->getCurrentToken() == "&amp;"
          or tok->getCurrentToken() == "|"
          or tok->getCurrentToken() == "&lt;"
          or tok->getCurrentToken() == "&gt;"
          or tok->getCurrentToken() == "="
          ){
        // op
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // term
        compileTerm();
    }
    
    XMLContent.push_back("</expression>");
}

void compilation_engine::compileTerm(){ // integerConstant | stringConstant | keywordConstant | varName | varName '[' expression ']' | subroutineCall | '(' expression ')' | unaryOp term
    
    XMLContent.push_back("<term>");
    
    // check if its an integerConstant or a stringConstant
    if(tok->tokenTypeString(tok->getCurrentToken()) == "integerConstant" or tok->tokenTypeString(tok->getCurrentToken()) == "stringConstant" or tok->tokenTypeString(tok->getCurrentToken()) == "keyword"){
        
        // we need to remove the quotation marks for the stringConstant. this will be handled seperately.
        
        if(tok->tokenTypeString(tok->getCurrentToken()) == "stringConstant"){
            
            string currToken = tok->getCurrentToken();
            // removing quotation marks
            currToken.erase(currToken.begin());
            currToken.erase(--currToken.end());
            
            XMLContent.push_back("<stringConstant> " + currToken + " </stringConstant>");
            tok->advance();
        
        }else{
            XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
            tok->advance();
        }
    }else if(tok->getCurrentToken() == "-" or tok->getCurrentToken() == "~"){ // unaryOp term
        // unaryOp
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // term
        compileTerm();
    }else if(tok->getCurrentToken() == "("){ // '(' expression ')'
        // '('
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // expression
        compileExpression();
        
        // ')'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();

    }else{ // this is where it gets LL(2). we need to know if this is varName, varName[expression] or a subroutine call.
        
        if(tok->hasMoreTokens()){
            string currentToken = tok->getCurrentToken();
            tok->advance();
            if(tok->getCurrentToken() == "["){ // now we know its in the form varName[expression]
                
                tok->retreat();
                
                // varName
                XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
                tok->advance();
                
                // '['
                XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
                tok->advance();
                
                // expression
                compileExpression();
                
                // ']'
                XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
                tok->advance();
                
            }else if(tok->getCurrentToken() == "("){
                // subroutineCall
                tok->retreat();
                compileSubroutineCall();
            }else if(tok->getCurrentToken() == "."){ // subroutineCall
                tok->retreat();
                
                compileSubroutineCall();
                
            }else{ // this has to be a varName
                tok->retreat();
                
                XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
                tok->advance();
            }
        }else{ // has to be a varName since there is only one token left. (honestly, i dont know where this case might show up)
            XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
            tok->advance();
        }
    }
    
    XMLContent.push_back("</term>");
}

void compilation_engine::compileExpressionList(){ // (expression (',' expression)*)?
    
    XMLContent.push_back("<expressionList>");
    
    if(tok->getCurrentToken() == ")"){
        XMLContent.push_back("</expressionList>");
        return; // handles the case where there are no expressions.
    }
    
    // expression
    compileExpression();
    
    while(tok->getCurrentToken() == ","){
        // ','
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // expression
        compileExpression();
    }
    
    XMLContent.push_back("</expressionList>");
    
}

void compilation_engine::compileSubroutineCall(){ // subroutineName '(' expressionList ')' | (className | varName) '.' subroutineName '(' expressionList ')'
    // this is also where the grammar becomes LL(2).
    // we need to check if the second token from now is a '(' or a '.'. That way we will know how to proceed further.
    
    tok->advance();
    
    if(tok->getCurrentToken() == "("){
            
        tok->retreat();
        
        // subroutineName
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // '('
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // expressionList
        compileExpressionList();
        
        // ')'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
    }else{ // second token is '.'
        
        tok->retreat();
        
        // (className | varName)
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // '.'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // subroutineName
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // '('
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // expressionList
        compileExpressionList();
        
        // ')'
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        
    }
    
    
}

void compilation_engine::compileParameterList(){ // ((type varName) (',' type VarName)*)?
    
    XMLContent.push_back("<parameterList>");
    
    if(tok->getCurrentToken() == ")"){ // zero parameters are handled here
        XMLContent.push_back("</parameterList>");
        return;
    }
    
    //type
    compileType();
    
    // varName
    XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
    tok->advance();
    
    
    // (',' type varName)*
    while(tok->getCurrentToken() != ")"){
        // ','
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
        
        // type
        compileType();
        
        // varName
        XMLContent.push_back("<" + tok->tokenTypeString(tok->getCurrentToken()) + "> " + tok->getCurrentToken() + " </" + tok->tokenTypeString(tok->getCurrentToken()) + ">");
        tok->advance();
    }
    
    
    XMLContent.push_back("</parameterList>");
    
}

