#ifndef SQLLITECLONE_SERIALIZER_H
#define SQLLITECLONE_SERIALIZER_H
#include <cereal/archives/binary.hpp>

#include "DataRow.h"

namespace SQLCore {
    template<class T>
    class Serializer {
    public:
        virtual ~Serializer() {};

        virtual bool serialize(T data) const = 0;

        virtual bool deserialize(T data) const = 0;
    };


    class BinarySerializer : public Serializer<SQLCore::DataRow> {

    };
}

#endif //SQLLITECLONE_SERIALIZER_H
