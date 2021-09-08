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
#include "../wal_logger_lib/WalQueue.h"

namespace SQLInterpreter {
    class Statement;
    class SqlFrontend;
}
namespace WALLogger {
    template<class T>
    class WalQueue;
}
namespace DbCore {
    class Repl {

    public:
        explicit Repl(WALLogger::WalQueue<SQLInterpreter::Statement>& q, SQLCore::DataTable& d_table, bool isSingleThreaded=false);
        Repl(const Repl& repl)=delete;
        Repl& operator=(const Repl& repl)=delete;
        typedef enum {
            META_COMMAND_SUCCESS,
            META_COMMAND_ERROR,
            META_COMMAND_EXIT,
            META_COMMAND_UNRECOGNIZED_COMMAND
        } MetaCommandResult;

        Repl();

        void execute();

    private:
        const std::string PROMPT = "db > ";
        SQLInterpreter::SqlFrontend d_sqlFrontEnd;
        SQLCore::DataTable& d_table;
        WALLogger::WalQueue<SQLInterpreter::Statement>& d_queue;
        bool d_is_single_threaded;
        inline void print_prompt() {
            std::cout << PROMPT;
        };

        std::unique_ptr<IoBuffer> readInput();

        MetaCommandResult executeMetaCommand(const std::unique_ptr<IoBuffer>& ioBuffer);

    };
}


#endif //SQLLITECLONE_REPL_H
