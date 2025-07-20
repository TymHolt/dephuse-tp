#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <fstream>
#include <string>

namespace pas {

    class SourceFile {
        private:
            std::ifstream& m_srcFileStream;
            uint m_line;
            uint m_column;

            std::string getPosString();

        public:
            SourceFile(std::ifstream& srcFileStream);
            void escalateError(std::string msg);
            char getCurrent();
            void toNext();
            bool hasEnded();
    };

}

#endif