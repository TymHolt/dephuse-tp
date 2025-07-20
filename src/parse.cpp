#include "parse.hpp"

pas::Program::Program() {

}

pas::Program *pas::parse(pas::TokenStream *tokenStream) {
    pas::Program *program = new pas::Program();
    
    pas::Token *programToken = tokenStream->getCurrent();
    if (programToken->getType() != pas::PAS_T_KW_PROGRAM) {
        tokenStream->escalateError(std::string("Unepexted token '") + programToken->getValue() +
            std::string("', expected 'program'"));
    }

    delete program;
    return program;
}