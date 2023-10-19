
#pragma once


#include "./tokenization.hpp"


struct NodeExpr { 

    Token int_lit;
      
};


struct NodeExit { 

    NodeExpr expr;

};







class Parser{
    
    public:
        inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))
        {

        }


        std::optional <NodeExpr> parse_expr()
        {
        
            if(peek().has_value() && peek().value().type == TokenType::int_lit)
            {
                return NodeExpr{.int_lit = consume()};
            }

            else 
            {
                return {};
            }


        }



        //For exit --> exit(expr)
        std::optional<NodeExit> parse()
        {
            std::optional <NodeExit> exit_node;
            while(peek().has_value())
            {
                if(expect(TokenType::exit, "No exit stmt found"))
                {

                    if (expect(TokenType::open_paren, "Missing a '(' "))
                    {
                        
                        
                        if(auto node_expr = parse_expr())   // Node_expr becomes true when there is a value returned by parse_expr
                        {

                                if(expect(TokenType::closed_paren, "Missing a ')' ")) 
                                {
                                    exit_node = NodeExit{.expr = node_expr.value()};   //store the value
                                }

                                else
                                {
                                    exit(EXIT_FAILURE);
                                }
                        }

                        else
                        {
                            std::cerr<<"Invalid Expression in exit(expr)"<<std::endl;
                            exit(EXIT_FAILURE);
                        }

                    }

                    else
                    {
                        exit(EXIT_FAILURE);
                    }


                }
                else
                {
                    exit(EXIT_FAILURE);
                }
                
                if(!expect (TokenType::semi, "No semi colon found after exit (expr)"))
                {
                    exit(EXIT_FAILURE);
                }
                
            }

            m_index = 0;
            return exit_node;


        }




    private:
        
        const std::vector<Token> m_tokens;
        size_t m_index = 0;           
        
        [[nodiscard]] inline const std::optional<Token> peek(int offset = 0)     //Return null if >=length of Tokens
        
            {
                if(m_index + offset >= m_tokens.size())
                {
                    return {};
                }
                else
                {
                    return m_tokens.at(m_index + offset);
                }

            }
    

            //Consume the Token i.e just take in the current character and move the pointer to the next character.
            inline Token consume()
            {
                
                return m_tokens.at(m_index++);
            }

            inline bool expect(TokenType expect,const std::string error_msg)
            {
                if(peek().has_value() && peek().value().type == expect)
                {
                    consume();
                    return true;
                }

                else
                {
                    std::cerr<<error_msg<<std::endl;
                    return false;
                }
            }



};