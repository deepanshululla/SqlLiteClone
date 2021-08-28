#include "Repl.h"

using namespace std;

namespace DbCore {

    [[noreturn]] void Repl::execute() {
        while (true) {
            print_prompt();
            std::unique_ptr<IoBuffer> ioBuffer = readInput();
            if (ioBuffer->data().find(".") == 0) {
                if (executeMetaCommand(ioBuffer) != META_COMMAND_SUCCESS) {
                    cout << "Unrecognized command: " << ioBuffer->data() << endl;;
                }
            }

            SQLInterpreter::Statement statement(ioBuffer->data());
            d_sqlFrontEnd->execute(statement);
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
            exit(EXIT_SUCCESS);
        } else {
            cout << "Unrecognized command: " << ioBuffer->data() << endl;;
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }

    Repl::Repl() : d_sqlFrontEnd(std::make_shared<SQLInterpreter::SqlFrontend>()) {

    }
}