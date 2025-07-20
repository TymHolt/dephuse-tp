#include <iostream>
#include <fstream>
#include "source.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "No source file given" << std::endl;
        return -1;
    }

    for (int srcFileIdx = 0; srcFileIdx < argc - 1; srcFileIdx++) {
        char *srcFileName = argv[srcFileIdx + 1];
        std::ifstream srcFileStream(srcFileName);
        
        if (!srcFileStream) {
            std::cout << "Unable to open file '" << srcFileName << "'" << std::endl;
            continue;
        }

        try {
            pas::SourceFile srcFile(srcFileStream);
            srcFile.escalateError("Test error");
        } catch (const std::runtime_error& ex) {
            std::cout << "Source file: " << srcFileName << std::endl;
            std::cout << ex.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown exception occurre" << std::endl;
        }

        srcFileStream.close();
    }

    return 0;
}