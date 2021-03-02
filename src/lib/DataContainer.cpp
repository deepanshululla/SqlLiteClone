#include "DataContainer.h"

namespace SQLCore {
    std::shared_ptr<DataContainer> getDataContainerFactory() {
        std::shared_ptr<DataContainer> dataContainer(new DataContainer);
        return dataContainer;
    }
    const bool DataContainer::addRow(std::shared_ptr<DataRow>& dataRow) {
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage());
        }
        d_pages.back()->addRow(dataRow);
        if (!d_dataSerializer->serialize(d_pages.back())){
            std::cerr <<"Failed to serialize data to file" << std::endl;
            return false;
        }
        return true;
    }

    void DataContainer::rows(std::vector<std::shared_ptr<DataRow>> &results) const {

        std::shared_ptr<Page> resultPage{nullptr};
        if (!d_dataSerializer->deserialize(resultPage)){
            std::cerr <<"Failed to deserialize data from file" << std::endl;

        }
        for (auto row : resultPage->rows()){
            results.push_back(row);
        }
    }

    DataContainer::DataContainer() :d_pages(std::vector<std::shared_ptr<Page>>{}),
            d_dataSerializer(getSerializer("/Users/deepanshululla/CLionProjects/sqlLiteClone/db.bin")) {

    }




}