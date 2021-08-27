#ifndef SQLLITECLONE_IOBUFFER_H
#define SQLLITECLONE_IOBUFFER_H


#include <string>
#include <iostream>

class IoBuffer {
private:
    const std::string d_buffer;
public:
    explicit IoBuffer(const std::string buffer) : d_buffer(buffer) {};
    IoBuffer(const IoBuffer& other)=delete;
    IoBuffer& operator=(const IoBuffer& other)=delete;

    inline bool isEmpty() const { return d_buffer.empty(); };

    inline const std::string &data() const { return d_buffer; };
};


#endif //SQLLITECLONE_IOBUFFER_H
