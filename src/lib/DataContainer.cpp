#include "DataContainer.h"

namespace SQLCore {
    std::shared_ptr<DataContainer> getDataContainerFactory() {
        std::shared_ptr<DataContainer> dataContainer(new DataContainer);
        return dataContainer;
    }
    const bool DataContainer::addRow(std::shared_ptr<DataRow> dataRow) {
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage());
        }
        d_pages.back()->addRow(dataRow);
        return true;;
    }

    void DataContainer::rows(std::vector<std::shared_ptr<DataRow>> &results) const {
        for (auto page: d_pages) {
            for (auto row: page->rows()){
                results.push_back(row);
            }
        }
    }
}