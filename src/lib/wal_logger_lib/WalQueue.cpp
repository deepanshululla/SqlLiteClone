#include "WalQueue.h"


namespace Wal {
    template<typename T>
    void WalQueue<T>::addToQueue(const T &item) {
        d_queue.emplace_back(item);
    }

    template<typename T>
    void WalQueue<T>::popFromQueue(T &item) {
        item = d_queue.front();
        d_queue.pop();
    }

}