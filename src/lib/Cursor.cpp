#include "Cursor.h"


namespace SQLCore{

    Cursor::Cursor(std::shared_ptr<DataTable>& datatable) :d_dataTable(datatable), d_rowNum(0), d_endOfTable(false){
        d_endOfTable = d_dataTable->isEmpty();
    }

    bool Cursor::advance() {
        if (d_endOfTable) {
            std::cerr << "End of sequence" << std::endl;
            return false;
        }
        d_rowNum++;
        if (d_rowNum>=d_dataTable->numRows()) {
            d_endOfTable = true;
        }
        return true;
    }

    std::shared_ptr<DataRow> Cursor::cursorValue() const {
        return d_dataTable->getRow(d_rowNum);
    }




}