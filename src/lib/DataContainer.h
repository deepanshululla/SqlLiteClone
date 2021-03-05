#ifndef SQLLITECLONE_DATACONTAINER_H
#define SQLLITECLONE_DATACONTAINER_H

#include <iostream>

#include "Serializer.h"

namespace SQLCore {
    const std::string DIRECTORY_LOCATION = "/Users/deepanshululla/CLionProjects/sqlLiteClone/data";

    class DataContainer {
    public:
        DataContainer(std::vector<std::shared_ptr<Page>> &pages, int numRows);

        const bool addRow(std::shared_ptr<DataRow> &dataRow);

        inline const int numRows() const { return d_numRows; };

        void setNumRows(int count) { d_numRows = count; };

        std::shared_ptr<Page> getLoadedPage(int pageId) const;

        void rows(std::vector<std::shared_ptr<DataRow>> &results) const;

    private:
        std::vector<std::shared_ptr<Page>> d_pages;
        int d_numRows;
        std::string d_directory;
        std::shared_ptr<Serializer<Page, int>> d_dataSerializer;
    };

    std::shared_ptr<DataContainer> getDataContainerFactory();

    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory);

    std::shared_ptr<Page> getPage(std::shared_ptr<DataContainer> &dataContainer, int pageId, std::string &directory);
}

#endif //SQLLITECLONE_DATACONTAINER_H
