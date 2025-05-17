
#pragma once


#include "./tokenization.hpp"
#include <variant>



struct NodeExpr_IntLit
{
    Token int_lit;
};

struct NodeExpr_Ident
{
    Token ident;
};

struct NodeExpr { 

    std::variant<NodeExpr_Ident,NodeExpr_IntLit> var_expr;
      
};

struct NodeStmt_Exit
{
    NodeExpr expr;
};

struct NodeStmt_Let
{
    Token ident;
    NodeExpr expr;
};

struct NodeStmt
{
    std::variant<NodeStmt_Exit, NodeStmt_Let> var_stmt;
};

struct NodeProg
{
    std::vector<NodeStmt> stmt;
};


class Parser{
    
    public:
        inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))
        {

        }


        std::optional <NodeExpr> parse_expr()
        {
            // expr-->int_lit |
            //        ident
                     
            if(peek().has_value() && peek().value().type == TokenType::int_lit)
            {
                return NodeExpr{.var_expr = NodeExpr_IntLit{.int_lit = consume()}};
            }

            else if (peek().has_value() && peek().value().type == TokenType::ident)
            {
                return NodeExpr{.var_expr = NodeExpr_Ident{.ident = consume()}};
            }

            else 
            {
                return {};
            }


        }

        //stmt --> exit(expr)
        //         let ident = expr;

        std::optional <NodeStmt> parse_stmt()
        {
            if(expect(TokenType::exit, "No exit stmt found"))
                {
                    NodeStmt_Exit stmt_exit;

                    if (expect(TokenType::open_paren, "Missing a '(' "))
                    {

                        
                        if(auto node_expr = parse_expr())   // Node_expr becomes true when there is a value returned by parse_expr
                        {

                                if(expect(TokenType::closed_paren, "Missing a ')' ")) 
                                {
                                    stmt_exit = NodeStmt_Exit{.expr = node_expr.value()};   //store the value
                                }

                                else
                                {   // for ')'
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
                        // for '('
                        exit(EXIT_FAILURE);
                    }


                    if(!expect (TokenType::semi, "No semi colon found after exit (expr)"))
                    {
                        exit(EXIT_FAILURE);
                    }


                return NodeStmt{.var_stmt = stmt_exit};   //Return the exit token with the expr

                }

                //let ident = expr;
        
            else if ( expect({TokenType::let}))    //consumes let

            {     
                if(check({TokenType::ident}))
                {    
                    auto stmt_let = NodeStmt_Let{.ident = consume()};
                    
                    if(expect({TokenType::eq},"Expected '=' after \"let ident\""))
                    {
                        if (auto expr = parse_expr())
                        {
                            stmt_let.expr =  expr.value();
                        }

                        else
                        {
                            std::cerr<<"Invalid Expression after \"let ident =\""<<std::endl;
                            exit(EXIT_FAILURE);
                        }

                        if(!expect({TokenType::semi}, "Expected ';' after \"let ident = expr\""))
                        {
                            exit(EXIT_FAILURE);
                        }

                    return NodeStmt{.var_stmt = NodeStmt_Let{stmt_let}};

                        
                    }

                    else
                    {
                        //for '='
                        exit(EXIT_FAILURE);
                    }

                }         

                else
                {
                    //for ident
                    std::cerr<<"Expected identifier after \"let\""<<std::endl;
                    exit(EXIT_FAILURE);
                }       
            

            }
            
            else
                { 
                    return {};
                } 
                

                
        }


    // for Start-> {Stmt}*
    std::optional<NodeProg> parse_prog()
    {
        NodeProg prog;

        while(peek().has_value())
        {
            if (auto stmt = parse_stmt())
            {
                prog.stmt.push_back(stmt.value());
            }

            else
            {
                std::cerr<<"I am not yet capable to recognise that statement"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
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

            inline bool expect(TokenType expect,const std::string error_msg="")   //Used to peek,consume / show error 
            {
                if(peek().has_value() && peek().value().type == expect)
                {
                    consume();
                    return true;
                }

                if(!error_msg.empty())
                {
                    std::cerr<<error_msg<<std::endl;
                    return false;
                }
            }

            inline bool check(TokenType check,int offset=0)
            {
                if(peek(offset).has_value() && peek(offset).value().type == check)
                {
                    return true;
                }

                else
                {
                    return false;
                }
            }



};