#include "MetaDataStore.h"


namespace SQLCore {

    bool MetaDataStore::addMapping(uint32_t cellNum, int pageId) {
        d_cellMapping[cellNum]=pageId;
        return true;
    }

    int MetaDataStore::getMapping(uint32_t cellNum) {
        auto it = d_cellMapping.find(cellNum);
        if (it == d_cellMapping.end()) {
            return -1;
        }
        return it->second;
    }
}