#include "Repl.h"

using namespace std;

namespace DbCore {

    [[noreturn]] void Repl::execute() {
        auto datatable = SQLCore::DataTable();
        while (true) {
            print_prompt();
            std::unique_ptr<IoBuffer> ioBuffer = readInput();
            if (ioBuffer->data().find(".") == 0) {
                auto result = executeMetaCommand(ioBuffer);
                if (result == META_COMMAND_EXIT) {
                    exit(EXIT_SUCCESS);
                }
                else if (result == META_COMMAND_UNRECOGNIZED_COMMAND) {
                    cout << "Unrecognized command: " << ioBuffer->data() << endl;
                }
            }

            SQLInterpreter::Statement statement(ioBuffer->data());
            d_sqlFrontEnd.execute(statement, datatable);
        }



    }

    std::unique_ptr<IoBuffer> Repl::readInput() {
        std::string inputString;
        std::getline(std::cin, inputString);
        std::unique_ptr<IoBuffer> ioBuffer(new IoBuffer(inputString));
        if (ioBuffer->isEmpty()) {
            cerr << "Error reading from input" << endl;
            exit(EXIT_FAILURE);
        }
        return std::move(ioBuffer);
    }

    Repl::MetaCommandResult Repl::executeMetaCommand(const std::unique_ptr<IoBuffer>& ioBuffer) {
        if (ioBuffer->data().find(".exit") == 0) {
            return META_COMMAND_EXIT;
        } else {
            cout << "Unrecognized command: " << ioBuffer->data() << endl;;
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }

    Repl::Repl() : d_sqlFrontEnd(SQLInterpreter::SqlFrontend{}) {

    }
}