#ifndef SQLLITECLONE_METADATASTORE_H
#define SQLLITECLONE_METADATASTORE_H
// Before including any cereal header file
#define CEREAL_THREAD_SAFE 1

#include <map>
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>

namespace SQLCore {
class MetaDataStore {
public:
    MetaDataStore()=default;
    MetaDataStore(const std::map<uint32_t,int>& cellMapping);
    int getMapping(uint32_t cellNum);
    MetaDataStore(const MetaDataStore& other)=delete;
    MetaDataStore& operator=(const MetaDataStore& other)=delete;
    bool addMapping(uint32_t cellNum, int pageId);
    template<class Archive>
    void serialize(Archive &archive) {
        archive(d_cellMapping);  // Simply list all the fields to be serialized/deserialized.
    }
    template<class Archive>
    static void load_and_construct(Archive &ar, cereal::construct<MetaDataStore> &construct) {
        std::map<uint32_t,int> cellMapping;
        ar(cellMapping);
        construct(cellMapping);
    }
private:
    std::map<uint32_t,int> d_cellMapping;

};
}



#endif //SQLLITECLONE_METADATASTORE_H
