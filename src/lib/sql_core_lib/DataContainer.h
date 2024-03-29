#ifndef SQLLITECLONE_DATACONTAINER_H
#define SQLLITECLONE_DATACONTAINER_H

#include <iostream>

#include "Serializer.h"
#include "MetaDataStore.h"

namespace SQLCore {

    class DataContainer {
    public:
        DataContainer(const std::string& fileDirectory, std::vector<std::shared_ptr<Page>> &pages, int numRows, const std::shared_ptr<MetaDataStore>& metaDataStore);
        DataContainer(const DataContainer& other)=delete;
        DataContainer& operator=(const DataContainer& other)=delete;
        const bool addRow(const std::shared_ptr<DataRow> &dataRow);

        inline const int numRows() const { return d_numRows; };
        std::shared_ptr<DataRow> getRow(uint32_t cellNumber) const;
        void setNumRows(int count) { d_numRows = count; };
        inline const int getPageId(uint32_t cellNumber) const { return d_metaStore->getMapping(cellNumber); };
        std::shared_ptr<Page> getLoadedPage(int pageId) const;
        void rows(std::vector<std::shared_ptr<DataRow>> &results) const;

    private:
        std::vector<std::shared_ptr<Page>> d_pages;
        int d_numRows;
        std::string d_directory;
        BinarySerializer<Page, int> d_dataSerializer;
        BinarySerializer<MetaDataStore, std::string> d_MetaSerializer;
        std::shared_ptr<MetaDataStore> d_metaStore;
    };
    std::unique_ptr<DataContainer> getDataContainerFactory(const std::string& fileDirectory);
    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory);
    void loadMetaData(const std::string &directory, std::shared_ptr<MetaDataStore>& result);


}

#endif //SQLLITECLONE_DATACONTAINER_H
