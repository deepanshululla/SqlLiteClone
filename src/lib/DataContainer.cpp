#include "DataContainer.h"


namespace SQLCore {
    std::shared_ptr<DataContainer> getDataContainerFactory() {
        std::vector<std::shared_ptr<Page>> pages;
        loadPages(pages, DIRECTORY_LOCATION);

        std::shared_ptr<DataContainer> dataContainer(new DataContainer(pages, 0));
        size_t numRowsInLastPage = dataContainer->getLoadedPage(pages.back()->id())->rows().size();
        dataContainer->setNumRows(numRowsInLastPage + (pages.size() - 1) * ROWS_PER_PAGE);
        return dataContainer;
    }

    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory) {
        std::vector<std::string> files;
        Utilities::Utils::getFileNamesFromDirectory(files, directory);
        for (auto file : files) {
            int id = getFileId(file);
            std::shared_ptr<Page> page(new Page(id));
            pages.push_back(page);
        }
    }

    std::shared_ptr<Page> getPage(std::shared_ptr<DataContainer> &dataContainer, int pageId, std::string &directory) {
        std::shared_ptr<Serializer<Page, int>> serializer = getSerializer(directory);
        std::shared_ptr<Page> page(new Page(pageId));
        serializer->deserialize(page, pageId);
        return page;
    }

    const bool DataContainer::addRow(std::shared_ptr<DataRow> &dataRow) {
        const int numPages = d_pages.size();
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage(numPages));
        }
        d_pages.back()->addRow(dataRow);
        ++d_numRows;
        if (!d_dataSerializer->serialize(d_pages.back(), d_pages.back()->id())) {
            std::cerr << "Failed to serialize data to file" << std::endl;
            return false;
        }
        return true;
    }

    void DataContainer::rows(std::vector<std::shared_ptr<DataRow>> &results) const {
        // fix bug here of d_pages not getting created on startup for old data.
        for (auto page : d_pages) {
            std::shared_ptr<Page> resultPage{nullptr};
            if (page->isUnloaded()) {
                resultPage = getLoadedPage(page->id());
            } else {
                resultPage = page;
            }
            for (auto row : resultPage->rows()) {
                results.push_back(row);
            }
        }

    }

    std::shared_ptr<Page> DataContainer::getLoadedPage(int pageId) const {
        if (pageId > d_pages.size()) {
            std::cerr << "Invalid Page Access" << std::endl;
            return std::shared_ptr<Page>(nullptr);
        }
        if (d_pages[pageId]->isUnloaded()) {
            //cache miss
            std::shared_ptr<Serializer<Page, int>> serializer = getSerializer(d_directory);
            std::shared_ptr<Page> page(new Page(pageId));
            serializer->deserialize(const_cast<std::shared_ptr<Page> &>(d_pages[pageId]), pageId);
        }
        return d_pages[pageId];
    }

    DataContainer::DataContainer(std::vector<std::shared_ptr<Page>> &pages, int numRows) : d_pages(pages),
                                                                                           d_numRows(numRows),
                                                                                           d_directory(
                                                                                                   SQLCore::DIRECTORY_LOCATION),
                                                                                           d_dataSerializer(
                                                                                                   getSerializer(
                                                                                                           SQLCore::DIRECTORY_LOCATION)) {

    }
}