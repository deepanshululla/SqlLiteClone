#include "DataTable.h"

namespace SQLCore {





bool DataTable::insert(std::shared_ptr<DataRow>& dataRow) {
    if (isFull()) {
        std::cout << "Data table is full."<<std::endl;
        return false;
    }
    d_dataContainer->addRow(dataRow);
    ++d_numRows;
    return true;
}

bool DataTable::fetchData(std::vector<std::shared_ptr<DataRow>> &results) {
    d_dataContainer->rows(results);
    if (results.empty()) {
        return false;
    }
    return true;
}

std::shared_ptr<DataRow> DataTable::getRow(int rowId) const {
    int pageId = rowId / TABLE_MAX_ROWS;
    std::shared_ptr<Page> page = getPage(pageId);
    // not needed, we can just compare size?
//    bool exists = std::binary_search(page->rows().begin(), page->rows().end(), [rowId](std::shared_ptr<DataRow> row) noexcept { return row->id()==rowId; });
//    if (!exists){
//        std::cout << "The element does not exist" <<std::endl;
//        return std::shared_ptr<DataRow>(nullptr);
//    }
    int rowPosition = rowId % TABLE_MAX_ROWS;
    return page->rows()[rowPosition];
}

}; //DBCore