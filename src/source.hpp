#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <fstream>
#include <string>

namespace pas {

    typedef struct SourcePos_Struct {
        uint m_line;
        uint m_column;
    } SourcePos;

    class SourceFile {
        private:
            std::ifstream& m_srcFileStream;
            SourcePos m_currentPos;
            std::string m_lineBuffer;

        public:
            SourceFile(std::ifstream& srcFileStream);
            void escalateError(std::string msg);
            char getCurrent();
            void toNext();
            bool hasEnded();
            SourcePos getCurrentPos();
    };

    std::string getPosString(pas::SourcePos pos);
}

#endif