#ifndef SQLLITECLONE_DATATABLE_H
#define SQLLITECLONE_DATATABLE_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <iostream>
#include "DataContainer.h"

namespace SQLCore {


// Idea is to use std::map which is a balanced btree to store objects using
// Primary Key -> DataRow
// Right now this will be only an in memory append only DB

const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;





class DataTable {
public:
    DataTable() :d_dataContainer(getDataContainerFactory()), d_numRows(0){d_numRows=d_dataContainer->numRows();};
    bool insert(std::shared_ptr<DataRow>& dataRow);
    inline const uint32_t numRows() const {return d_numRows;};
    inline const bool isEmpty() const {return d_numRows==0;};
    std::shared_ptr<DataRow> getRow(int rowId) const;

    inline const bool isFull() const {return d_numRows==TABLE_MAX_ROWS;};
    bool fetchData(std::vector<std::shared_ptr<DataRow>>& results);
private:
    inline std::shared_ptr<Page> getPage(int pageId) const {return d_dataContainer->getPage(pageId);};
    std::shared_ptr<DataContainer> d_dataContainer;
    uint32_t d_numRows;
};
}


#endif //SQLLITECLONE_DATATABLE_H
