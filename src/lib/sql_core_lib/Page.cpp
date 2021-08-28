#include "Page.h"

namespace SQLCore {
    std::shared_ptr<Page> getNewPage(int id) {
        std::shared_ptr<Page> page(new Page(id));
        return page;
    }

    bool Page::addRow(const std::shared_ptr<DataRow>& dataRow) {
        auto it = d_rows.find(dataRow->id());
        if (it != d_rows.end()) {
            std::cout << "Error: Duplicate key." << std::endl;
            return false;
        }
        d_rows[dataRow->id()] = dataRow;
        return true;
    }

    Page::Page(uint32_t id) : d_id(id), d_rows(std::map<uint32_t,std::shared_ptr<DataRow>>{}), d_isUnloaded(true) {

    }


    Page::Page(uint32_t id, std::map<uint32_t,std::shared_ptr<DataRow>> &rows) : d_id(id), d_rows(rows), d_isUnloaded(false) {

    }

    std::shared_ptr<DataRow> Page::getRow(uint32_t id) const{
        auto it = d_rows.find(id);
        if (it == d_rows.end()) {
            std::cout << "Error: Cannot find row." << std::endl;
            return  std::shared_ptr<DataRow>{nullptr};
        }
        return it->second;

    }


}