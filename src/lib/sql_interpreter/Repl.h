//
// Created by Deepanshu Lulla on 2/16/21.
//

#ifndef SQLLITECLONE_REPL_H
#define SQLLITECLONE_REPL_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <map>
#include "IOBuffer.h"
#include "SqlFrontend.h"


namespace SQLInterpreter {
    class Statement;
    class SqlFrontend;
}
namespace DbCore {
    class Repl {

    public:
        Repl(const Repl& repl)=delete;
        Repl& operator=(const Repl& repl)=delete;
        typedef enum {
            META_COMMAND_SUCCESS,
            META_COMMAND_UNRECOGNIZED_COMMAND
        } MetaCommandResult;

        Repl();

        [[noreturn]] void execute();

    private:
        const std::string PROMPT = "db > ";
        SQLInterpreter::SqlFrontend d_sqlFrontEnd;

        inline void print_prompt() {
            std::cout << PROMPT;
        };

        std::unique_ptr<IoBuffer> readInput();

        MetaCommandResult executeMetaCommand(const std::unique_ptr<IoBuffer>& ioBuffer);

    };
}


#endif //SQLLITECLONE_REPL_H
