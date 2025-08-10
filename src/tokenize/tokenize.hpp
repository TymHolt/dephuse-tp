#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <fstream>
#include "source.hpp"

namespace pas {

    enum TokenType {
        PAS_T_STREAM_END,

        PAS_T_IDENTIFIER,    // ...

        // Values
        PAS_T_V_STRING,      // '...'

        // Keywords
        PAS_T_KW_PROGRAM,    // program
        PAS_T_KW_BEGIN,      // begin
        PAS_T_KW_END,        // end

        // Controls
        PAS_T_PERIOD,        // .
        PAS_T_SEMICOLON,     // ;
        PAS_T_PARENT_OPEN,   // (
        PAS_T_PARENT_CLOSE   // )    
    };

    class Token {
        private:
            TokenType m_type;
            std::string m_value;
            pas::SourcePos m_srcPos;

        public:
            Token(TokenType type, std::string value, pas::SourcePos srcPos);
            TokenType getType();
            std::string getValue();
            pas::SourcePos getSourcePos();
    };

    class TokenStream {
        private:
            pas::SourceFile& m_srcFile;
            Token *m_current;
            bool m_currentInitialized;
    
        public:
            TokenStream(pas::SourceFile& srcFile);
            ~TokenStream();
            void toNext();
            Token *getCurrent();
            bool hasEnded();
            void escalateError(std::string msg);
    };
}

#endif