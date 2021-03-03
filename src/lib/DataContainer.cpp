#include "DataContainer.h"


namespace SQLCore {
    std::shared_ptr<DataContainer> getDataContainerFactory() {
        std::vector<std::shared_ptr<Page>> pages;
        loadPages(pages,DIRECTORY_LOCATION);
        std::shared_ptr<DataContainer> dataContainer(new DataContainer(pages));
        return dataContainer;
    }

    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory) {
        std::vector<std::string> files;
        Utilities::Utils::getFileNamesFromDirectory(files, directory);
        std::shared_ptr<Serializer<Page, int>> serializer = getSerializer(directory);
        for (auto file : files){
            int id = getFileId(file);
            std::shared_ptr<Page> page(new Page(id));
            serializer->deserialize(page, id);
            pages.push_back(page);
        }

    }

    const bool DataContainer::addRow(std::shared_ptr<DataRow>& dataRow) {
        const int numPages = d_pages.size();
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage(numPages));
        }
        d_pages.back()->addRow(dataRow);
        if (!d_dataSerializer->serialize(d_pages.back(), d_pages.back()->id())){
            std::cerr <<"Failed to serialize data to file" << std::endl;
            return false;
        }
        return true;
    }

    void DataContainer::rows(std::vector<std::shared_ptr<DataRow>> &results) const {
        // fix bug here of d_pages not getting created on startup for old data.
        for (auto page : d_pages) {
            std::shared_ptr<Page> resultPage{nullptr};
            if (!d_dataSerializer->deserialize(resultPage, page->id())){
                std::cerr <<"Failed to deserialize data from file" << std::endl;

            }
            for (auto row : resultPage->rows()){
                results.push_back(row);
            }
        }
    }

    DataContainer::DataContainer() :d_pages(std::vector<std::shared_ptr<Page>>{}),
            d_dataSerializer(getSerializer(SQLCore::DIRECTORY_LOCATION)) {
    }

    DataContainer::DataContainer(std::vector<std::shared_ptr<Page>>& pages) :d_pages(pages),  d_dataSerializer(getSerializer(SQLCore::DIRECTORY_LOCATION)) {

    }
}