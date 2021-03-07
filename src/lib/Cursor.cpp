#include "Cursor.h"


namespace SQLCore {

    Cursor::Cursor(std::shared_ptr<DataTable> &datatable) : d_dataTable(datatable),
                                                            d_endOfTable(datatable->isEmpty()),
                                                            d_pageNum(datatable->rootPageNum()),
                                                            d_cellNum(0),
                                                            d_rootNode(getNode(NODE_ROOT, datatable->getPage(
                                                                    datatable->rootPageNum()))) {

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
        return d_dataTable->getRow(d_pageNum, d_cellNum);
    }


    void insertNode(std::shared_ptr<Cursor> &cursor, uint32_t key, std::shared_ptr<DataRow> &dataRow) {
        std::shared_ptr<Node> node = getNode(NODE_LEAF, cursor->getPageById(cursor->pageNum()));
        int numCellsInPage = node->numCells();
        if (cursor->cellNum() < numCellsInPage) {


        }
    }

    std::shared_ptr<Cursor> getCursor(std::shared_ptr<DataTable>& datatable) {
        return std::shared_ptr<Cursor>(new Cursor(datatable));
    }
}