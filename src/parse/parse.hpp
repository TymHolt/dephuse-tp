#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <vector>
#include "tokenize/tokenize.hpp"

namespace pas {

    class AstNode {
        
    };

    class ProgramNode : public AstNode {
        private:
            std::string m_name;
            std::vector<AstNode *> m_statementNodes;
        public:
            ProgramNode(std::string name);
            void addStatement(AstNode *statementNode);
            std::vector<AstNode *> getStatementNodes();
    };

    class FunctionCallNode : public AstNode {
        private:
            std::string m_callName;
            std::vector<AstNode *> m_argumentNodes;
        public:
            FunctionCallNode(std::string callName);
            void addArgument(AstNode *argumentNode);
            std::vector<AstNode *> getArgumentNodes();
    };

    class StringLiteralNode : public AstNode {
        private:
            std::string m_value;
        public:
            StringLiteralNode(std::string value);
            std::string getValue();
    };

    class Parser {
        private:
            pas::TokenStream *m_tokenStream;
            Token *expectToken(pas::TokenType type, std::string expectErrorMsg);
            std::string expectGetString(pas::TokenType type, std::string expectErrorMsg);
            bool tryConsumeToken(pas::TokenType type);
            AstNode *parseExpression();
            AstNode *parseWithIdentifier(); 
        public:
            Parser(pas::TokenStream *tokenStream);
            ProgramNode *parse();
    };
}

#endif