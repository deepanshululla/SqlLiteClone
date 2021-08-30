#ifndef SQLLITECLONE_CURSOR_H
#define SQLLITECLONE_CURSOR_H

#include "DataTable.h"

namespace SQLCore {
    class Cursor {
        //to do: implement it as an iterator
    public:
        explicit Cursor(DataTable &datatable);
        Cursor(const Cursor & other)=delete;
        Cursor& operator=(const Cursor& other)=delete;
        inline const uint32_t pageNum() const { return d_pageNum;};
        inline const uint32_t cellNum() const {return d_cellNum;};
        std::shared_ptr<DataRow> cursorValue() const;
        inline const std::shared_ptr<Page> getPageById(int pageId) const;
        inline bool isEnd() const { return d_endOfTable; };
        bool advance();
        bool advance(int position);
        bool insert(const std::shared_ptr<DataRow> &dataRow) const;
    private:
        DataTable& d_t;
        uint32_t d_pageNum;
        uint32_t d_cellNum;
        bool d_endOfTable;
    };
    std::shared_ptr<Cursor> getCursor(DataTable &datatable);
}

#endif //SQLLITECLONE_CURSOR_H
