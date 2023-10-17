#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include<sstream>

#pragma once // Only processes the header once preventing errors

// Tokenizer

enum class TokenType // Used for pushing the keywords
{
    exit,
    int_lit,
    semi
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};



class Tokenizer
{

public:

    inline explicit Tokenizer(const std::string src) : m_src(std::move(src)) // std::move transfers content to the m_src
    {
        //intialise member list
    }

    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf = ""; // Stores our tokens

        while(peek().has_value())

        {
            if(std::isalpha(peek().value()))
            {
                buf.push_back(consume());

                while(peek().has_value() && std::isalnum(peek().value()))
                {
                    buf.push_back(consume());
                }

                if(buf=="exit")
                {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                }

                else
                {
                    std::cerr<<"Exit token doesnt exist"<<std::endl;
                    exit(EXIT_FAILURE);
                }

            }

            else if(std::isspace(peek().value()))
            {
                consume();
                continue;
            }

            else if (std::isdigit(peek().value()))
            {
                buf.push_back(consume());

                while(peek().has_value() && std::isdigit(peek().value()))
                {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit,.value = buf});
                buf.clear();
                continue;
            }

            else if(peek().value() == ';')
            {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }

            else{
                std::cerr<<"No suitable token found"<<std::endl;
                exit(EXIT_FAILURE);
                
            }
        }
        m_index = 0;
        return tokens;
    }

private:

    const std::string m_src;   //for the input file
    size_t m_index = 0;           //for storing the current character index
    
    [[nodiscard]] inline const std::optional<char> peek(int ahead = 0)     //Return null if >=length  of file or current char
    
        {
            if(m_index + 1 > m_src.length())
            {
                return {};
            }
            else
            {
                return m_src.at(m_index + ahead);
            }

        }
 

        //Consume the character i.e just take in the current character and move the pointer to the next character.
        inline char consume()
        {
            
            return m_src.at(m_index++);
        }

};