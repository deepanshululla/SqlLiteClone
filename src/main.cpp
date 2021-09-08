#include "./lib/sql_interpreter_lib/Repl.h"

#include <thread>
#include <iostream>
#include <memory>

const std::string DIRECTORY_LOCATION = "/Users/deepanshululla/CLionProjects/sqlLiteClone/data";
WALLogger::WalQueue<SQLInterpreter::Statement> q{};
SQLCore::DataTable dataTable{DIRECTORY_LOCATION};


void produce() {
    while (true){
        DbCore::Repl repl(q, dataTable);
        repl.execute();
    }
}

void consume() {
    while (true) {
        while (!q.isEmpty()) {
            SQLInterpreter::Statement s;
            q.popFromQueue(s);
            auto cursor = SQLCore::Cursor(dataTable);
            std::vector<std::string> dataParts;
            if (!(SQLInterpreter::InsertStatement::extract(dataParts, s.statementString()))) {
                throw std::runtime_error("Could not extract statement");
            }
            if (!(SQLInterpreter::InsertStatement::validate(dataParts))) {
                throw std::runtime_error("Could not validate statement");
            }
            std::shared_ptr<SQLCore::DataRow> dataRow(
                    new SQLCore::DataRow(static_cast<uint32_t>(std::stoi(dataParts[1])),
                                         dataParts[2],
                                         dataParts[3]));

            if (cursor.insert(dataRow)) {
//                std::cout << "Executed." << std::endl;
            }
        }
    }


}

int main() {

    try{
        std::thread p(produce);

        std::thread c(consume);

        p.join();
        c.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

    }



}
