#ifndef SQLLITECLONE_SERIALIZER_H
#define SQLLITECLONE_SERIALIZER_H


#include "Page.h"
#include "Utils.h"
#include "Serializer.h"
namespace Utils {
    class Utils;
}
namespace SQLCore {
    template <class T, class Id>
    class Serializer {
    public:
        virtual ~Serializer() {};
        virtual bool serialize(std::shared_ptr<T> data, Id id) const = 0;
        virtual bool deserialize(std::shared_ptr<T>& data, Id id) const = 0;
    };
    template <class T, class Id>
    class BinarySerializer : public Serializer<T, Id>{
    public:
        // The general copy constructor
        template<typename U, typename V>                       // member template
        explicit BinarySerializer(const BinarySerializer<U, V>& other);
        explicit BinarySerializer<T, Id>(const std::string& fileDirectory);
        bool serialize(std::shared_ptr<T> data, Id id) const;
        bool deserialize(std::shared_ptr<T>& data,  Id id) const;
    private:
        std::string d_fileDirectory;
        void getFileName(Id id, std::string& fileName) const;

    };
    int getFileId(std::string &fileName);
    std::shared_ptr<Serializer<Page, int>> getSerializer(const std::string& fileName);
}

#endif //SQLLITECLONE_SERIALIZER_H
