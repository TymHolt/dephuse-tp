#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <string>
#include <fstream>
#include "source.hpp"

namespace pas {

    enum TokenType {
        PAS_T_STREAM_END,

        PAS_T_IDENTIFIER,    // 

        // Values
        PAS_T_V_STRING,      // '...'

        // Keywords
        PAS_T_KW_PROGRAM,    // program
        PAS_T_KW_BEGIN,      // begin
        PAS_T_KW_END, // end.

        // Controls
        PAS_T_PERIOD,
        PAS_T_SEMICOLON,
        PAS_T_PARENT_OPEN,   // (
        PAS_T_PARENT_CLOSE   // )    
    };

    class Token {
        private:
            TokenType m_type;
        public:
            Token(TokenType type);
            virtual ~Token() {

            }
            TokenType getType();
    };

    class StringValueToken : public Token {
        private:
            std::string m_value;

        public:
            StringValueToken(TokenType type, std::string value);
            std::string getValue();
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
    };
}

#endif