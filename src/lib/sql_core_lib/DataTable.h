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
        DataTable(const std::string& fileDirectory);
        DataTable(const DataTable& other)=delete;
        DataTable& operator=(const DataTable& other)=delete;

        bool insert(const std::shared_ptr<DataRow> &dataRow);

        inline const uint32_t numRows() const { return d_dataContainer->numRows(); };

        inline const bool isEmpty() const { return d_dataContainer->numRows() == 0; };

        std::shared_ptr<DataRow> getRow(uint32_t cellNumber) const;
        const int getPageId(uint32_t cellNumber) const;
        inline const uint32_t rootPageNum() const { return d_rootPageNum; };

        inline const bool isFull() const { return d_dataContainer->numRows() == TABLE_MAX_ROWS; };
        std::shared_ptr<Page> getPage(int pageId) const;
    private:
        std::unique_ptr<DataContainer> d_dataContainer;
        uint32_t d_rootPageNum=0;
    };
}


#endif //SQLLITECLONE_DATATABLE_H
