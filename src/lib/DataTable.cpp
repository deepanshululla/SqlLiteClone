#include "DataTable.h"

namespace SQLCore {





bool DataTable::insert(std::shared_ptr<DataRow> dataRow) {
    if (isFull()) {
        std::cout << "Data table is full."<<std::endl;
        return false;
    }
    d_dataContainer->addRow(dataRow);
    ++numRows;
    return true;
}

bool DataTable::fetchData(std::vector<std::shared_ptr<DataRow>> &results) {
    d_dataContainer->rows(results);
    if (results.empty()) {
        return false;
    }
    return true;
}

}; //DBCore