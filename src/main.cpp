#include "./lib/sql_interpreter_lib/Repl.h"

#include <thread>
#include <iostream>
#include "Config.h"

const std::string DIRECTORY_LOCATION(Config::get_directory());
WALLogger::WalQueue<SQLInterpreter::Statement> q;
SQLCore::DataTable dataTable{DIRECTORY_LOCATION};
bool use_single_thread = Config::use_single_thread();


void produce() {
    while (true){
        DbCore::Repl repl(q, dataTable, use_single_thread);
        repl.execute();
    }
}

void consume() {
    while (true) {
        while (!q.isEmpty()) {
            SQLInterpreter::Statement s;
            q.popFromQueue(s);
            auto cursor = SQLCore::Cursor(dataTable);
            executeInsertImpl(s, cursor);
        }
    }
}





int main() {
    if (!use_single_thread) {
        try {
            std::thread p(produce);

            std::thread c(consume);

            p.join();
            c.join();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;

        }
    } else {
       produce();
    }


}
