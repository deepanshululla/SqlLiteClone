#ifndef SQLLITECLONE_SERIALIZER_H
#define SQLLITECLONE_SERIALIZER_H


#include "Page.h"
#include <cereal/archives/binary.hpp>

#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>


namespace SQLCore {
    template <class T>
    class Serializer {
    public:
        virtual ~Serializer() {};

        virtual bool serialize(std::shared_ptr<T>& data) const = 0;

        virtual bool deserialize(std::shared_ptr<T>& data) const = 0;
    };
    template <class T>
    class BinarySerializer : public Serializer<T>{
    public:
        // The general copy constructor
        template<typename U>                       // member template
        explicit BinarySerializer(const BinarySerializer<U>& other);
        explicit BinarySerializer<T>(const std::string& fileName);
        bool serialize(std::shared_ptr<T>& data) const;
        bool deserialize(std::shared_ptr<T>& data) const;
    private:
        std::string d_fileName;

    };

    std::shared_ptr<Serializer<Page>> getSerializer(const std::string& fileName);
    std::shared_ptr<Serializer<DataRow>> getRowSerializer(const std::string& fileName);
}

#endif //SQLLITECLONE_SERIALIZER_H
