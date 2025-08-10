#include "tokenize.hpp"

pas::Token::Token(pas::TokenType type, std::string value, pas::SourcePos srcPos)
    : m_type(type) 
    , m_value(value)
    , m_srcPos(srcPos) {

}

pas::TokenType pas::Token::getType() {
    return m_type;
}

std::string pas::Token::getValue() {
    return m_value;
}

pas::SourcePos pas::Token::getSourcePos() {
    return m_srcPos;
}

pas::TokenStream::TokenStream(pas::SourceFile& srcFile) 
    : m_srcFile(srcFile)
    , m_current(new pas::Token(PAS_T_STREAM_END, "", {0, 0})) {
    toNext();
}

pas::TokenStream::~TokenStream() {
    if (m_current != 0)
        delete m_current;
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphaNum(char c) {
    return isAlpha(c) || isNum(c);
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// TODO Make state to class, method to handle char.
// toNext() is already too big
enum TokenizeState {
    SEARCHING,
    READING_WORD,
    READING_STRING,
    READING_STRING_ESCAPED
};

void pas::TokenStream::toNext() {
    m_currentInitialized = true;
    delete m_current;
    m_current = 0;

    TokenizeState state = SEARCHING;
    std::string valueBuffer = "";
    SourcePos tokenPos = {0, 0};

    while (!m_srcFile.hasEnded()) {
        char c = m_srcFile.getCurrent();

        switch (state) {
            case SEARCHING:
                tokenPos = m_srcFile.getCurrentPos();

                if (isAlpha(c)) {
                    state = READING_WORD;
                    valueBuffer += c;
                } else if (c == '.') {
                    m_current = new pas::Token(PAS_T_PERIOD, ".", tokenPos);
                    m_srcFile.toNext(); // Consume read char
                    return;
                } else if (c == ';') {
                    m_current = new pas::Token(PAS_T_SEMICOLON, ";", tokenPos);
                    m_srcFile.toNext(); // Consume read char
                    return;
                } else if (c == '(') {
                    m_current = new pas::Token(PAS_T_PARENT_OPEN, "(", tokenPos);
                    m_srcFile.toNext(); // Consume read char
                    return;
                } else if (c == ')') {
                    m_current = new pas::Token(PAS_T_PARENT_CLOSE, ")", tokenPos);
                    m_srcFile.toNext(); // Consume read char
                    return;        
                } else if (c == '\'') {
                    state = READING_STRING;
                } else if (!isWhitespace(c))
                    m_srcFile.escalateError(std::string("Unexpected char '") + c + 
                        std::string("'"));

                break;

            case READING_WORD:                
                if (!isAlphaNum(c)) {
                    // TODO Make not case sensitive
                    if (valueBuffer == "program") {
                        m_current = new pas::Token(PAS_T_KW_PROGRAM, valueBuffer, tokenPos);
                    } else if (valueBuffer == "begin") {
                        m_current = new pas::Token(PAS_T_KW_BEGIN, valueBuffer, tokenPos);
                    } else if (valueBuffer == "end") {
                        m_current = new pas::Token(PAS_T_KW_END, valueBuffer, tokenPos);
                    } else {
                        m_current = new pas::Token(PAS_T_IDENTIFIER, valueBuffer, tokenPos);
                    }

                    return;
                }

                valueBuffer += c;
                break;    
            
            case READING_STRING:
                if (c == '\'') {
                    m_srcFile.toNext(); // The ' should not be read again
                    m_current = new pas::Token(PAS_T_V_STRING, valueBuffer, tokenPos);
                    return;
                } else if (c == '\\') {
                    state = READING_STRING_ESCAPED;
                } else {
                    valueBuffer += c;
                }

                break;

            case READING_STRING_ESCAPED:
                if (c == 'n') {
                    valueBuffer += '\n';
                } else if (c == 't') {
                    valueBuffer += '\t';
                } else if (c == 'r') {
                    valueBuffer += '\r';
                } else if (c == '0') {
                    valueBuffer += '\0';
                } else {
                    valueBuffer += c;
                }

                state = READING_STRING;
                break;

            default:
                m_srcFile.escalateError(std::string("Internal: Unknown tokenize state"));
                break;
        }

        m_srcFile.toNext();
    }

    if (state == READING_WORD) {
        m_current = new pas::Token(PAS_T_V_STRING, valueBuffer, tokenPos);
        return;
    }

    if (state == READING_STRING || state == READING_STRING_ESCAPED) {
        m_srcFile.escalateError("String not closed");
    }

    m_current = new pas::Token(PAS_T_STREAM_END, "", {0, 0});
}

pas::Token *pas::TokenStream::getCurrent() {
    if (!m_currentInitialized)
        toNext();
    
    return m_current;
}

bool pas::TokenStream::hasEnded() {
    return m_current->getType() == PAS_T_STREAM_END;
}

void pas::TokenStream::escalateError(std::string msg) {
    throw std::runtime_error(std::string("ERROR ") + getPosString(m_current->getSourcePos()) +
        std::string(" -> ") + msg);
}