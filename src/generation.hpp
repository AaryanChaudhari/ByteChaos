#pragma once

#include "./parser.hpp"

class Generator{

    public:
        inline  Generator(NodeProg prog) 
        : m_prog(std::move(prog))
        {

        }


        [[nodiscard]] const std::string gen_stat(const NodeStmt &stmt)
        {
            
        }

        [[nodiscard]] const std::string  gen_prog(){
             
            std::stringstream output;
            output<<"global _start\n";
            output<<"_start: \n";
            
            for(const NodeStmt stmt: m_prog.stmt)
            {
                output<<gen_stat(stmt);
            }



            output << "    mov rax,60\n";
            output << "    mov rdi,0\n";
            output << "    syscall";

            return output.str();        
              
        }

    private:
    const NodeProg m_prog;


};