#include "Cursor.h"


namespace SQLCore {

    Cursor::Cursor(const std::shared_ptr<DataTable> &datatable) : d_dataTable(datatable),
                                                            d_endOfTable(datatable->isEmpty()),
                                                            d_pageNum(datatable->rootPageNum()),
                                                            d_cellNum(0)
                                                            {

    }

    bool Cursor::advance() {
        if (d_endOfTable) {
            std::cerr << "End of sequence" << std::endl;
            return false;
        }

        ++d_cellNum;

        if (!d_endOfTable && d_cellNum >= d_dataTable->numRows()) {
            d_endOfTable = true;
            return false;
        }
        if (d_cellNum%ROWS_PER_PAGE==0) {
            ++d_pageNum;
        }

        return true;

    }

    std::shared_ptr<DataRow> Cursor::cursorValue() const {
        return d_dataTable->getRow(d_cellNum);
    }

    bool Cursor::insert(const std::shared_ptr<DataRow> &dataRow) const {

        return d_dataTable->insert(dataRow);
    };

    bool Cursor::advance(int position) {
        d_cellNum = position;
        if (!d_endOfTable && d_cellNum > d_dataTable->numRows()) {
            d_endOfTable = true;
            return false;
        }
        d_pageNum = d_dataTable->getPageId(position);
        return true;
    }

    std::shared_ptr<Cursor> getCursor(const std::shared_ptr<DataTable>& datatable) {
        return std::shared_ptr<Cursor>(new Cursor(datatable));
    }
}