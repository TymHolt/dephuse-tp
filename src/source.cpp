#include "source.hpp"
#include <stdexcept>

pas::SourceFile::SourceFile(std::ifstream& srcFileStream)
    : m_srcFileStream(srcFileStream) {
        m_line = 1;
        m_column = 1;
}

std::string pas::SourceFile::getPosString() {
    return std::string("(") + std::to_string(m_line) + std::string(":") + 
        std::to_string(m_column) + std::string(")");
}

void pas::SourceFile::escalateError(std::string msg) {
    throw std::runtime_error(std::string("ERROR ") + getPosString() + std::string(" -> ") + msg);
}

char pas::SourceFile::getCurrent() {
    return (char) m_srcFileStream.peek();
}

void pas::SourceFile::toNext() {
    char c = getCurrent();

    if (c == '\n') {
        m_line++;
        m_column = 1;
    } else
        m_column++;

    m_srcFileStream.get();
}

bool pas::SourceFile::hasEnded() {
    return m_srcFileStream.peek() == EOF;
}