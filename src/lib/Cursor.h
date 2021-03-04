#ifndef SQLLITECLONE_CURSOR_H
#define SQLLITECLONE_CURSOR_H

#include "DataTable.h"

namespace SQLCore {
class Cursor {
    //to do: implement it as an iterator
public:
    Cursor(std::shared_ptr<DataTable>& datatable);
    std::shared_ptr<DataRow> cursorValue() const;
    inline bool isEnd() const { return d_endOfTable;};
    bool advance();
private:
    std::shared_ptr<DataTable> d_dataTable;
    uint32_t d_rowNum;
    bool d_endOfTable;
};
}

#endif //SQLLITECLONE_CURSOR_H
