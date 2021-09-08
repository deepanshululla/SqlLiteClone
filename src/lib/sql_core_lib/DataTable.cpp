#include "DataTable.h"

namespace SQLCore {
    bool DataTable::insert(const std::shared_ptr<DataRow> &dataRow) {
        if (isFull()) {
            throw std::runtime_error("Failed to insert since table is full");
        }
        d_dataContainer->addRow(dataRow);
        return true;
    }

    std::shared_ptr<DataRow> DataTable::getRow(uint32_t cellNumber) const {
        return d_dataContainer->getRow(cellNumber);
    }

    DataTable::DataTable(const std::string& fileDirectory)  :d_dataContainer(getDataContainerFactory(fileDirectory)){
    }

    const int DataTable::getPageId(uint32_t cellNumber) const { return d_dataContainer->getPageId(cellNumber);}

    std::shared_ptr<Page> DataTable::getPage(int pageId) const { return d_dataContainer->getLoadedPage(pageId); };

}; //SQLCore