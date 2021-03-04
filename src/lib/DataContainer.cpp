#include "DataContainer.h"


namespace SQLCore {
    std::shared_ptr<DataContainer> getDataContainerFactory() {
        std::vector<std::shared_ptr<Page>> pages;
        int numRows = loadPages(pages,DIRECTORY_LOCATION);
        std::shared_ptr<DataContainer> dataContainer(new DataContainer(pages, numRows));
        return dataContainer;
    }

    int loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory) {
        std::vector<std::string> files;
        Utilities::Utils::getFileNamesFromDirectory(files, directory);
        std::shared_ptr<Serializer<Page, int>> serializer = getSerializer(directory);
        int numRows =0;
        for (auto file : files){
            int id = getFileId(file);
            std::shared_ptr<Page> page(new Page(id));
            serializer->deserialize(page, id);
            pages.push_back(page);
            numRows += page->rows().size();
        }
        return numRows;

    }

    const bool DataContainer::addRow(std::shared_ptr<DataRow>& dataRow) {
        const int numPages = d_pages.size();
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage(numPages));
        }
        d_pages.back()->addRow(dataRow);
        ++d_numRows;
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
            d_dataSerializer(getSerializer(SQLCore::DIRECTORY_LOCATION)), d_numRows(0){
    }

    DataContainer::DataContainer(std::vector<std::shared_ptr<Page>>& pages) :d_pages(pages),  d_dataSerializer(getSerializer(SQLCore::DIRECTORY_LOCATION)), d_numRows(0) {

    }

    std::shared_ptr<Page> DataContainer::getPage(int pageId) const{
        if (pageId>d_pages.size()) {
            std::cerr << "Invalid Page Access" << std::endl;
            return std::shared_ptr<Page>(nullptr);
        }
        return d_pages[pageId];

    }

    DataContainer::DataContainer(std::vector<std::shared_ptr<Page>> &pages, int numRows) : d_pages(pages),  d_dataSerializer(getSerializer(SQLCore::DIRECTORY_LOCATION)), d_numRows(numRows) {

    }
}