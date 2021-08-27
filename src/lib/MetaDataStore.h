#ifndef SQLLITECLONE_METADATASTORE_H
#define SQLLITECLONE_METADATASTORE_H

#include <map>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>

namespace SQLCore {
class MetaDataStore {
public:
    int getMapping(uint32_t cellNum);
    // fixme: copy constructors are compulsory
//    MetaDataStore(const MetaDataStore& other)=delete;
//    MetaDataStore& operator=(const MetaDataStore& other)=delete;
    bool addMapping(uint32_t cellNum, int pageId);
    template<class Archive>
    void serialize(Archive &archive) {
        archive(d_cellMapping);  // Simply list all the fields to be serialized/deserialized.
    }

private:
    std::map<uint32_t,int> d_cellMapping;

};
}



#endif //SQLLITECLONE_METADATASTORE_H
