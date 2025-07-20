#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <vector>
#include "tokenize.hpp"

namespace pas {

    class Instruction {
        public:
            virtual std::string getCodeC();
            virtual std::vector<std::string> getIncludes();
    };

    class WriteLnInstruction {
        
    };

    class Program {
        private:
            std::vector<std::string> m_includes;
            std::vector<std::string> m_instructions;
            
        public:
            Program();
            std::string getCodeC();
            void addInstrcution();
    };

    Program *parse(pas::TokenStream *tokenStream);
}

#endif