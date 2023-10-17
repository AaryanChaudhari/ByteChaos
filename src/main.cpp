#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
// #include "./parser.hpp"
// #include "./tokenization.hpp"
#include "./generation.hpp"









//Token To Assembly




int main(int argc, char *argv[])

{

    // Checking whether the input file is specifiedd or not
    if (argc != 2)
    {
        std::cerr << "No Input Files" << std::endl;
        std::cerr << "Input Usage: ./build/okto <input.okto>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents; // taking a string object
    {
        std::stringstream content_stream;
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();            // returns a pointer to the start of input file till the end.
        contents = content_stream.str();
    }

    //Generate Tokens from input file 

    Tokenizer tokenizer(std::move(contents)); 
    std::vector<Token> token = tokenizer.tokenize();


    //Generate Parse Tree
    Parser parsetree(std::move(token));        //Moves token to the private member variable
    std::optional <NodeExit> tree = parsetree.parse();   //returns the root and the tree i.e. for now exit(expr)


    //Generate Code using Tokens
    
    if(!tree.has_value())   //check if null i.e. Parse didnt return exit 
    {
        std::cerr<<"No exit statement found"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    Generator c_generate(tree.value());         //Moves the root to the private member variable 
    std::string asem = c_generate.generate();

    { 
        std::fstream output("./src/i_files/main.asm",std::ios::out);
        output << asem;
    
    }

    system("nasm -felf64 ./src/i_files/main.asm");
    system("ld -o ./src/i_files/main ./src/i_files/main.o");
    

    return EXIT_SUCCESS;
    
}