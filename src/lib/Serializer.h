#ifndef SQLLITECLONE_SERIALIZER_H
#define SQLLITECLONE_SERIALIZER_H


#include "DataRow.h"


namespace SQLCore {
    template <class T>
    class Serializer {
    public:
        virtual ~Serializer() {};

        virtual bool serialize(T data) const = 0;

        virtual bool deserialize(T data) const = 0;
    };
    template <class T>
    class BinarySerializer : public Serializer<T>{
    public:
        template<typename U>                       // member template
        BinarySerializer(const BinarySerializer<U>& other);
        BinarySerializer<T>(const std::string& fileName);
        bool serialize(T data) const;
        bool deserialize(T data) const;
    private:
        std::string d_fileName;

    };

    std::shared_ptr<Serializer<DataRow>> getSerializer(const std::string& fileName);
}

#endif //SQLLITECLONE_SERIALIZER_H
