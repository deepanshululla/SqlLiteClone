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



template <class T>
class Command {
public:
    typedef void(T:: *Method)();
    Command(T* t, Method f):d_object(t), d_method(f){};
    inline void execute() const{ d_object->d_method;};
private:

    const T* d_object;
    const Method d_method;
    // prohibit copying
    Command(const Command& c);
    Command& operator=(const Command&);
};



class Repl {

public:
    typedef enum {
        META_COMMAND_SUCCESS,
        META_COMMAND_UNRECOGNIZED_COMMAND
    } MetaCommandResult;
    Repl();
    [[noreturn]] void execute();
private:
    const std::string PROMPT ="db>";
    const std::shared_ptr<SQLInterpreter::SqlFrontend> d_sqlFrontEnd;
    inline void print_prompt() {
        std::cout << PROMPT;
    };
    std::shared_ptr<IoBuffer> readInput();
    MetaCommandResult executeMetaCommand(std::shared_ptr<IoBuffer> ioBuffer);

};
}



#endif //SQLLITECLONE_REPL_H
