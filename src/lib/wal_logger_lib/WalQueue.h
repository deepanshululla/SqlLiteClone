#ifndef SQLLITECLONE_WALLOGGER_H
#define SQLLITECLONE_WALLOGGER_H

#include <queue>

namespace WALLogger {

template <typename T>
class WalQueue {
public:
    WalQueue(){};
    WalQueue(const WalQueue<T> & other)=delete;
    WalQueue& operator=(const WalQueue<T> & other)=delete;
    void addToQueue(const T& item);
    void popFromQueue(T& item);
    inline bool isEmpty() {return d_queue.empty();};
private:
    std::queue<T> d_queue;

};
template<typename T>
void WalQueue<T>::addToQueue(const T &item) {
    d_queue.push(item);
}

template<typename T>
void WalQueue<T>::popFromQueue(T &item) {
    item = d_queue.front();
    d_queue.pop();
}
}



#endif //SQLLITECLONE_WALLOGGER_H
