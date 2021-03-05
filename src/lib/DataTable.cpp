#include "DataTable.h"

namespace SQLCore {


    bool DataTable::insert(std::shared_ptr<DataRow> &dataRow) {
        if (isFull()) {
            std::cout << "Data table is full." << std::endl;
            return false;
        }
        d_dataContainer->addRow(dataRow);
        return true;
    }

    std::shared_ptr<DataRow> DataTable::getRow(int rowId) const {
        int pageId = rowId / TABLE_MAX_ROWS;
        std::shared_ptr<Page> page = getPage(pageId);
        int rowPosition = rowId % TABLE_MAX_ROWS;
        return page->rows()[rowPosition];
    }

    DataTable::DataTable() : d_dataContainer(getDataContainerFactory()) {};

    std::shared_ptr<DataTable> getDataTableFactory() {
        return std::shared_ptr<DataTable>(new DataTable());
    }

}; //DBCore