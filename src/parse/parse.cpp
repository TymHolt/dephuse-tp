#include "parse.hpp"

pas::Parser::Parser(pas::TokenStream *tokenStream) 
    : m_tokenStream(tokenStream) {

}

pas::Token *pas::Parser::expectToken(pas::TokenType type, std::string expectErrorMsg) {
    pas::Token *token = m_tokenStream->getCurrent();

    if (token->getType() != type) {
        m_tokenStream->escalateError(std::string("Unexpected token '") + token->getValue() + 
            std::string("', ") + expectErrorMsg);
    }

    m_tokenStream->toNext();
    return token;
}

std::string pas::Parser::expectGetString(pas::TokenType type, std::string expectErrorMsg) {
    Token *token = expectToken(type, expectErrorMsg);
    return token->getValue();
}

bool pas::Parser::tryConsumeToken(pas::TokenType type) {
    if (m_tokenStream->getCurrent()->getType() == type) {
        m_tokenStream->toNext();
        return true;
    }

    return false;
}

pas::AstNode *pas::Parser::parseExpression() {
    return new StringLiteralNode(expectGetString(pas::PAS_T_V_STRING, "expected string value"));
}

pas::AstNode *pas::Parser::parseWithIdentifier() {
    std::string identifier = expectGetString(pas::PAS_T_IDENTIFIER, "expected identifier");

    FunctionCallNode *funcCallNode;
    if (tryConsumeToken(pas::PAS_T_PARENT_OPEN)) {
        funcCallNode = new FunctionCallNode(identifier);

        // TODO Arguments not splitted by ','
        while (m_tokenStream->getCurrent()->getType() != pas::PAS_T_PARENT_CLOSE) {
            funcCallNode->addArgument(parseExpression());
        }

        // TODO Possible memory leak. Maybe local creation and copy into new?
        expectToken(pas::PAS_T_PARENT_CLOSE, "')' expected");
    }

    expectToken(pas::PAS_T_SEMICOLON, "';' expected");
    return funcCallNode;
}

pas::ProgramNode *pas::Parser::parse() {
    expectToken(pas::PAS_T_KW_PROGRAM, "expected program definition");
    pas::ProgramNode *programNode = new pas::ProgramNode(
        expectGetString(pas::PAS_T_IDENTIFIER, "expected program name"));
    expectToken(pas::PAS_T_SEMICOLON, "';' expected");
    expectToken(pas::PAS_T_KW_BEGIN, "'begin' expected");
    
    while (m_tokenStream->getCurrent()->getType() != pas::PAS_T_KW_END) {
        programNode->addStatement(parseWithIdentifier());
    }

    expectToken(pas::PAS_T_KW_END, "'end' expected");
    expectToken(pas::PAS_T_PERIOD, "'.' expected");
    
    return programNode;
}