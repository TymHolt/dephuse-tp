#include "source.hpp"
#include <stdexcept>

pas::SourceFile::SourceFile(std::ifstream& srcFileStream)
    : m_srcFileStream(srcFileStream) {
        m_line = 1;
        m_column = 0;
}

std::string pas::SourceFile::getPosString() {
    return std::string("(") + std::to_string(m_line) + std::string(":") + 
        std::to_string(m_column) + std::string(")");
}

void pas::SourceFile::escalateError(std::string msg) {
    throw std::runtime_error(std::string("ERROR ") + getPosString() + std::string(" -> ") + msg);
}