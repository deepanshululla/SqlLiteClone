#include "Page.h"

namespace SQLCore {
    std::shared_ptr<Page> getNewPage(int id) {
        std::shared_ptr<Page> page(new Page(id));
        return page;
    }
    bool Page::addRow(std::shared_ptr<DataRow> dataRow) {
        d_rows.push_back(dataRow);
        return true;
    }

    Page::Page(int id) :d_id(id),d_rows(std::vector<std::shared_ptr<DataRow>> {}){

    }



    Page::Page(int id, std::vector<std::shared_ptr<DataRow>> &rows) :d_id(id),d_rows(rows){

    }


}