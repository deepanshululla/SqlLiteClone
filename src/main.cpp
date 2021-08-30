
#include "./lib/sql_interpreter_lib/Repl.h"

using namespace std;



//void produce(Wal::WalQueue<SQLInterpreter::Statement>& q) {
//
//}
//
//void consume(Wal::WalQueue<SQLInterpreter::Statement>& q) {
//
//}

int main() {
//    Wal::WalQueue<SQLInterpreter::Statement> q{};
//    consume(q);
//    produce(q);

    DbCore::Repl repl;
    repl.execute();


}
