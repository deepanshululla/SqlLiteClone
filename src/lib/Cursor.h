#ifndef SQLLITECLONE_CURSOR_H
#define SQLLITECLONE_CURSOR_H

#include "DataTable.h"
#include "Btree.h"

namespace SQLCore {
    class Cursor {
        //to do: implement it as an iterator
    public:
        Cursor(std::shared_ptr<DataTable> &datatable);
        inline const uint32_t pageNum() const { return d_pageNum;};
        inline const uint32_t cellNum() const {return d_cellNum;};
        std::shared_ptr<DataRow> cursorValue() const;

        inline const std::shared_ptr<Page> getPageById(int pageId) const { return d_dataTable->getPage(pageId);};
        inline bool isEnd() const { return d_endOfTable; };
        bool advance();
        bool advance(int position);
        bool insert(const std::shared_ptr<DataRow>& dataRow ) const;
    private:
        std::shared_ptr<DataTable> d_dataTable;
        uint32_t d_pageNum;
        uint32_t d_cellNum;
        std::shared_ptr<Node> d_rootNode;
        bool d_endOfTable;
    };
    void insertNode(std::shared_ptr<Cursor>& cursor, uint32_t key, std::shared_ptr<DataRow>& dataRow);
    std::shared_ptr<Cursor> getCursor(std::shared_ptr<DataTable> &datatable);
}

#endif //SQLLITECLONE_CURSOR_H
