#ifndef SQLLITECLONE_SERIALIZER_H
#define SQLLITECLONE_SERIALIZER_H

#include "MetaDataStore.h"
#include "Page.h"
#include "Utils.h"
#include "Serializer.h"
#include <string>

namespace Utils {
    class Utils;
}
namespace SQLCore {
    template<class T, class Id>
    class Serializer {
    public:
        virtual ~Serializer() {};
        virtual bool serialize(std::shared_ptr<T> data, Id id) const = 0;
        virtual bool deserialize(std::shared_ptr<T>& data, Id id) const = 0;
    };

    template<class T, class Id>
    class BinarySerializer : public Serializer<T, Id> {
    public:
        explicit BinarySerializer<T, Id>(const std::string &fileDirectory);
        bool serialize(std::shared_ptr<T> data, Id id) const;
        bool deserialize(std::shared_ptr<T>& data, Id id) const;
        // mark copy operations as restricted
        BinarySerializer<T, Id>(const BinarySerializer<T, Id>& other)=delete;
        BinarySerializer<T, Id>& operator=(const BinarySerializer<T, Id>& other)=delete;
    private:
        std::string d_fileDirectory;

        auto conv_to_string(Id val) const;

        void getFileName(Id id, std::string &fileName) const;

    };

    int getFileId(std::string &fileName);

    template<class T, typename Id>
    BinarySerializer<T, Id>::BinarySerializer(const std::string &fileDirectory) :d_fileDirectory(fileDirectory) {

    }
    template class BinarySerializer<Page, int>;
    template class BinarySerializer<MetaDataStore, std::string>;
}

#endif //SQLLITECLONE_SERIALIZER_H
