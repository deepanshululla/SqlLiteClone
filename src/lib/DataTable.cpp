#include "DataTable.h"

namespace SQLCore {


    bool DataTable::insert(std::shared_ptr<DataRow> &dataRow) {
        if (isFull()) {
            std::cout << "Error: Table full." << std::endl;
            return false;
        }
        d_dataContainer->addRow(dataRow);
        return true;
    }

    std::shared_ptr<DataRow> DataTable::getRow(int pageId, int cellNumber) const {
        std::shared_ptr<Page> page = getPage(pageId);
        return page->rows()[cellNumber%ROWS_PER_PAGE];
    }

    DataTable::DataTable() : d_dataContainer(getDataContainerFactory()) {};

    std::shared_ptr<DataTable> getDataTableFactory() {
        return std::shared_ptr<DataTable>(new DataTable());
    }

}; //DBCore