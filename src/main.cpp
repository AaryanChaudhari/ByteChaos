#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>



// Tokenizer

enum class TokenType         //Used for pushing the keywords
{
    _return,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};



//Token To Assembly

std::string token_to_assembly(const std::vector<Token> &tokens)   
{
    std::stringstream output;
    output<<"global _start\n";
    output<<"_start: \n";
 


    for(int i = 0; i < tokens.size(); i++)
    {
        const Token& token = tokens.at(i);
        
        if(token.type==TokenType::_return)
        {            
            if(i+1<tokens.size() && tokens.at(i+1).type == TokenType::int_lit)
            {
                if(i+2<tokens.size() && tokens.at(i+2).type == TokenType::semi)
                {
                    output << "    mov rax,60\n";
                    output << "    mov rdi, " << tokens.at(i+1).value.value()<<"\n";
                    output << "    syscall";
                }
            }
        }
    }

    return output.str();

}







std::vector<Token> tokenize(const std::string &str)
{

    std::vector<Token> tokens;
    std::string buf = "";             //Stores our tokens


    for(int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);                 //Also checks inbound errors 
        
        if(std::isalpha(c))
        {
            buf.push_back(c);
            i++;

                while(std::isalnum(str.at(i)))
                {
                    buf.push_back(str.at(i));                
                    i++;
                }
                i--;

            if(buf=="return")
            {
                tokens.push_back({.type=TokenType::_return});
                buf.clear();
            } 

            else
            {
                std::cerr<<"Not a 'return' token"<<std::endl;
                exit(EXIT_FAILURE);
            }

        }
        else if (std::isspace(c))
        {
            continue;
        }

        else if(std::isdigit(c))
        {
            buf.push_back(c);
            i++;

                while(std::isdigit(str.at(i)))
                {
                    buf.push_back(str.at(i));
                    i++;
                }
                i--;

            tokens.push_back({.type=TokenType::int_lit,.value=buf});
            buf.clear();
        }

        else if(c == ';')
        {
            tokens.push_back({.type=TokenType::semi});
        }
        
        else
        {
            std::cerr<<"No Suitable Token Found"<<std::endl;
            exit(EXIT_FAILURE);
        }

    
    
    
    }

    return tokens;

}

int main(int argc, char *argv[])

{

    // Checking whether the input file is specifiedd or not
    if (argc != 2)
    {
        std::cerr << "No Input Files" << std::endl;
        std::cerr << "Input Usage: ./build/nib <input.nib>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents; // taking a string object
    {
        std::stringstream content_stream;
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();            // returns a pointer to the start of input file till the end.
        contents = content_stream.str();
    }

    
    std::vector<Token> token = tokenize(contents); // Generate Tokens..

    std::string asem = token_to_assembly(token);

    { 
        std::fstream output("./src/main.asm",std::ios::out);
        output << asem;
    
    }

    system("nasm -felf64 ./src/main.asm");
    system("ld -o main ./src/main.o");
    

    return EXIT_SUCCESS;
    //Changed this
}