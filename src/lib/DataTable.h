#ifndef SQLLITECLONE_DATATABLE_H
#define SQLLITECLONE_DATATABLE_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include "DataContainer.h"

namespace SQLCore {


// Idea is to use std::map which is a balanced btree to store objects using
// Primary Key -> DataRow
// Right now this will be only an in memory append only DB

const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;





class DataTable {
public:
    DataTable() :d_dataContainer(getDataContainerFactory()){};
    bool insert(std::shared_ptr<DataRow> dataRow);
    inline const bool isFull() const {return numRows==TABLE_MAX_ROWS;};
    bool fetchData(std::vector<std::shared_ptr<DataRow>>& results);
private:
    std::shared_ptr<DataContainer> d_dataContainer;
    uint32_t numRows;
};
}


#endif //SQLLITECLONE_DATATABLE_H
