#ifndef SQLLITECLONE_WALLOGGER_H
#define SQLLITECLONE_WALLOGGER_H

#include <queue>
//#include "../sql_interpreter_lib/Statement.h"

namespace Wal {
    template <typename T>
    class WalQueue {
    public:
        WalQueue()=default;
        WalQueue(const WalQueue<T> & other)=delete;
        WalQueue& operator=(const WalQueue<T> & other)=delete;
        void addToQueue(const T& item);
        void popFromQueue(T& item);
    private:
        std::queue<T> d_queue;

    };

//    template class WalQueue<SQLInterpreter::Statement>;

}



#endif //SQLLITECLONE_WALLOGGER_H
