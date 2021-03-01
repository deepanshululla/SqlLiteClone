#ifndef SQLLITECLONE_PAGE_H
#define SQLLITECLONE_PAGE_H

#include <memory>
#include <vector>
#include "DataRow.h"
#include <cereal/archives/binary.hpp>

namespace SQLCore {
    const uint32_t ROW_SIZE = sizeof(DataRow);

    const int MAX_PAGE_SIZE = 4096;
    const int TABLE_MAX_PAGES = 100;
    const uint32_t ROWS_PER_PAGE = MAX_PAGE_SIZE / ROW_SIZE;
    class Page {
    public:
        Page();
        inline const bool isFull() const{return d_rows.size() == ROWS_PER_PAGE;};
        bool addRow(std::shared_ptr<DataRow> dataRow);
        inline const std::vector<std::shared_ptr<DataRow>> rows() const {
            return d_rows;
        }

    private:
        std::vector<std::shared_ptr<DataRow>> d_rows;
        template<class Archive>
        void serialize(Archive& archive)
        {
            std::vector<DataRow> serResults{};
            for (auto row : d_rows) {
                serResults.push_back(*row);
            }
            archive(serResults);  // Simply list all the fields to be serialized/deserialized.
        }
    };
    std::shared_ptr<Page> getNewPage();
};
#endif //SQLLITECLONE_PAGE_H
