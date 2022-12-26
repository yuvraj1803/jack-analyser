# jack-analyser (tokenizer + parser)
 
Author: Yuvraj Sakshith
 
The Jack Analyser is a module of the Jack Compiler.

It consists of two sub-modules, the **Tokenizer and the Compilation-Engine (aka Parser)**.

**Tokenizer** : Reads the given .jack file and breaks it into tokens. It can provide the next token sequentially by the Tokenizer-API.

***Tokenizer-API:***

               * tokenizer::advance() -> moves to the next token

               * tokenizer::retreat() -> moves to the previous token
               
               * tokenizer::hasMoreTokens() -> returns true if more tokens remaining, otherwise false
               
               * tokenizer::getCurrentToken() -> returns the current token
               
               * tokenizer::tokenType() -> returns the token type. (types present in ref/ref.h)
               
               ...

**Compilation-Engine (Parser)** :  uses the services of the Tokenizer through the Tokenizer-API and generates an XML file.
                          This is done recursively by following the **Jack Grammar**.
                     

<img width="1407" alt="compiler-design" src="https://user-images.githubusercontent.com/37622719/209528715-2e73424f-bcad-4463-bb24-dfbc9c3440d0.png">

**Jack Grammar** 
Jack Grammar is a LL-Grammar which is LL(1) in all cases except while handling expressions, in which it becomes LL(2).
(Parsed from **LEFT TO RIGHT** and by constructing the **LEFT MOST DERIVATION** of the sentence.)

Refer to the Jack Grammar and the design of the compiler in the images below.
![jack-grammar](https://user-images.githubusercontent.com/37622719/209528502-0515d747-ceb5-4839-b6e3-28a89e3122b8.png)


                     

