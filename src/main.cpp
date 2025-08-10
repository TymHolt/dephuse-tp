#include <iostream>
#include <fstream>
#include "source.hpp"
#include "tokenize/tokenize.hpp"
#include "parse/parse.hpp"

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

        pas::SourceFile srcFile(srcFileStream);
        pas::TokenStream *tokenStream = new pas::TokenStream(srcFile);
        pas::Parser parser(tokenStream);

        try {
            delete parser.parse();
        } catch (const std::runtime_error& ex) {
            std::cout << "Source file: " << srcFileName << std::endl;
            std::cout << ex.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown exception occurred" << std::endl;
        }

        delete tokenStream;
        srcFileStream.close();
    }

    return 0;
}