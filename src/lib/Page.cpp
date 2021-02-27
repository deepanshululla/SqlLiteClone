#include "Page.h"

namespace SQLCore {
    std::shared_ptr<Page> getNewPage() {
        std::shared_ptr<Page> page(new Page);
        return page;
    }
    bool Page::addRow(std::shared_ptr<DataRow> dataRow) {
        d_rows.push_back(dataRow);
        return true;
    }

    Page::Page() :d_rows(std::vector<std::shared_ptr<DataRow>>{}){

    }

}