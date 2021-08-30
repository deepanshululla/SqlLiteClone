#include "DataTable.h"

namespace SQLCore {


    bool DataTable::insert(const std::shared_ptr<DataRow> &dataRow) {
        if (isFull()) {
            std::cout << "Error: Table full." << std::endl;
            return false;
        }
        d_dataContainer->addRow(dataRow);
        return true;
    }

    std::shared_ptr<DataRow> DataTable::getRow(uint32_t cellNumber) const {
        return d_dataContainer->getRow(cellNumber);
    }

    DataTable::DataTable() : d_dataContainer(getDataContainerFactory()) {}

    const int DataTable::getPageId(uint32_t cellNumber) const { return d_dataContainer->getPageId(cellNumber);}

    std::shared_ptr<Page> DataTable::getPage(int pageId) const { return d_dataContainer->getLoadedPage(pageId); };

    std::shared_ptr<DataTable> getDataTableFactory() {
        return std::shared_ptr<DataTable>(new DataTable());
    }

}; //DBCore