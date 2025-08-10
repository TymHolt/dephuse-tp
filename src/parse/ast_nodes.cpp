#include "parse/parse.hpp"

// ProgramNode

pas::ProgramNode::ProgramNode(std::string name) {
    m_name = name;
}

void pas::ProgramNode::addStatement(AstNode *statementNode) {
    m_statementNodes.push_back(statementNode);
}

std::vector<pas::AstNode *> pas::ProgramNode::getStatementNodes() {
    return m_statementNodes;
}

// FunctionCallNode

pas::FunctionCallNode::FunctionCallNode(std::string callName) {
    m_callName = callName;
}

void pas::FunctionCallNode::addArgument(AstNode *argumentNode) {
    m_argumentNodes.push_back(argumentNode);
}

std::vector<pas::AstNode *> pas::FunctionCallNode::getArgumentNodes() {
    return m_argumentNodes;
}

// StringLiteralNode

pas::StringLiteralNode::StringLiteralNode(std::string value) {
    m_value = value;
}

std::string pas::StringLiteralNode::getValue() {
    return m_value;
}