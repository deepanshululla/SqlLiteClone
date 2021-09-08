#ifndef SQLLITECLONE_WALLOGGER_H
#define SQLLITECLONE_WALLOGGER_H

#include <queue>
#include <mutex>
#include <exception>

namespace WALLogger {

    struct EmptyQueue : std::exception {
        const char *what() const throw() {
            return "EmptyQueue";
        }
    };

    template<typename T>
    class WalQueue {
    public:
        WalQueue() {};

        WalQueue(const WalQueue<T> &other);

        WalQueue &operator=(const WalQueue<T> &other) = delete;

        void addToQueue(T item);

        void popFromQueue(T &item);

        bool isEmpty() const;
    private:
        std::queue <T> d_queue;
        mutable std::mutex d_mutex;
    };

    template<typename T>
    void WalQueue<T>::addToQueue(T item) {
        std::lock_guard <std::mutex> lock(d_mutex);
        d_queue.push(std::move(item));
    }

    template<typename T>
    void WalQueue<T>::popFromQueue(T &item) {
        std::lock_guard <std::mutex> lock(d_mutex);
        if (d_queue.size() == 0) {
            throw EmptyQueue();
        }
        item = d_queue.front();
        d_queue.pop();
    }

    template<typename T>
    WalQueue<T>::WalQueue(const WalQueue<T> &other) {
        std::lock_guard <std::mutex> lock(d_mutex);
        d_queue = other.d_queue;
    }

    template<typename T>
    bool WalQueue<T>::isEmpty() const{
        std::lock_guard <std::mutex> lock(d_mutex);
        return d_queue.empty();
    }
}


#endif //SQLLITECLONE_WALLOGGER_H
