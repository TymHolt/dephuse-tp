#include "tokenize.hpp"

pas::Token::Token(pas::TokenType type)
    : m_type(type){

}

pas::TokenType pas::Token::getType() {
    return m_type;
}

pas::StringValueToken::StringValueToken(pas::TokenType type, std::string value)
    : Token(type)
    , m_value(value) {

}

std::string pas::StringValueToken::getValue() {
    return m_value;
}

pas::TokenStream::TokenStream(pas::SourceFile& srcFile) 
    : m_srcFile(srcFile)
    , m_current(new pas::Token(PAS_T_STREAM_END)) {
    toNext();
}

pas::TokenStream::~TokenStream() {
    delete m_current;
}

enum TokenizeState {
    SEARCHING,
    READING_VALUE
};

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphaNum(char c) {
    return isAlpha(c) || isNum(c);
}

void pas::TokenStream::toNext() {
    delete m_current;

    TokenizeState state = SEARCHING;
    std::string valueBuffer = "";

    Outer:
    while (!m_srcFile.hasEnded()) {
        char c = m_srcFile.getCurrent();

        switch (state) {
            case SEARCHING:
                if (isAlpha(c)) {
                    state = READING_VALUE;
                    valueBuffer += c;
                }
                break;

            case READING_VALUE:
                if (!isAlphaNum(c)) {
                    m_current = new pas::StringValueToken(PAS_T_V_STRING, valueBuffer);
                    return;
                }

                valueBuffer += c;
                break;    
            
            default:
                m_srcFile.escalateError("Internal: Unknown tokenize state");
                break;
        }

        m_srcFile.toNext();
    }

    if (state == READING_VALUE) {
        m_current = new pas::StringValueToken(PAS_T_V_STRING, valueBuffer);
        return;
    }

    m_current = new pas::Token(PAS_T_STREAM_END);
}

pas::Token *pas::TokenStream::getCurrent() {
    return m_current;
}

bool pas::TokenStream::hasEnded() {
    return m_current->getType() == PAS_T_STREAM_END;
}