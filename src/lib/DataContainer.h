#ifndef SQLLITECLONE_DATACONTAINER_H
#define SQLLITECLONE_DATACONTAINER_H

#include <iostream>

#include "Serializer.h"
#include "MetaDataStore.h"

namespace SQLCore {
    const std::string DIRECTORY_LOCATION = "/Users/deepanshululla/CLionProjects/sqlLiteClone/data";

    class DataContainer {
    public:
        DataContainer(std::vector<std::shared_ptr<Page>> &pages, int numRows, std::shared_ptr<MetaDataStore>& metaDataStore);

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
        std::shared_ptr<Serializer<Page, int>> d_dataSerializer;
        std::shared_ptr<Serializer<MetaDataStore, std::string>> d_MetaSerializer;
        std::shared_ptr<MetaDataStore> d_metaStore;
    };


    std::shared_ptr<DataContainer> getDataContainerFactory();
    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory);
    std::shared_ptr<MetaDataStore> loadMetaData(const std::string &directory);


}

#endif //SQLLITECLONE_DATACONTAINER_H
