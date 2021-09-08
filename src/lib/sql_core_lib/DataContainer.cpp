#include "DataContainer.h"
#include <regex>

namespace SQLCore {
    std::unique_ptr<DataContainer> getDataContainerFactory(const std::string& fileDirectory) {
        std::vector<std::shared_ptr<Page>> pages{};
        loadPages(pages, fileDirectory);
        std::shared_ptr<MetaDataStore> metaDataStore = std::make_shared<MetaDataStore>();
        loadMetaData(fileDirectory, metaDataStore);
        std::unique_ptr<DataContainer> dataContainer = std::make_unique<DataContainer>(fileDirectory, pages, 0, metaDataStore);
        size_t numRowsInLastPage = 0;
        if (!pages.empty()) {
            numRowsInLastPage = dataContainer->getLoadedPage(pages.back()->id())->rows().size();
            dataContainer->setNumRows(numRowsInLastPage + (pages.size() - 1) * ROWS_PER_PAGE);
        }
        return dataContainer;
    }

    void loadPages(std::vector<std::shared_ptr<Page>> &pages, const std::string &directory) {
        std::vector<std::string> files;
        Utilities::Utils::getFileNamesFromDirectory(files, directory);
        const std::regex r("[0-9]+(.bin)");

        for (auto &file : files) {
            if (std::regex_match(file, r)) {
                int id = getFileId(file);
                std::shared_ptr<Page> page(new Page(id));
                pages.push_back(page);
            }

        }
    }

    void loadMetaData(const std::string &directory, std::shared_ptr<MetaDataStore> &metaDataStore) {
        BinarySerializer<MetaDataStore, std::string> metaSerializer(directory);
        std::vector<std::string> files;
        Utilities::Utils::getFileNamesFromDirectory(files, directory);
        const std::regex r("index.bin");
        for (auto file : files) {
            if (std::regex_match(file, r)) {
                metaSerializer.deserialize(metaDataStore, "index");
            }
        }

    }


    const bool DataContainer::addRow(const std::shared_ptr<DataRow> &dataRow) {
        const int numPages = d_pages.size();
        if (d_pages.empty() || d_pages.back()->isFull()) {
            d_pages.emplace_back(getNewPage(numPages));
        }
        d_pages.back()->addRow(dataRow);
        d_metaStore->addMapping(dataRow->id(), d_pages.size() - 1);

        ++d_numRows;

        // todo: need to be in some sort of transaction
        // otherwise in case of failure might lead to consistency bugs
        if (!d_MetaSerializer.serialize(d_metaStore, "index")) {
            std::cerr << "Failed to serialize metadata to file" << std::endl;
            return false;
        }
        if (!d_dataSerializer.serialize(d_pages.back(), d_pages.back()->id())) {
            std::cerr << "Failed to serialize data to file" << std::endl;
            return false;
        }

        return true;
    }

    void DataContainer::rows(std::vector<std::shared_ptr<DataRow>> &results) const {
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
        if (d_pages.empty()) {
            return std::shared_ptr<Page>(nullptr);
        }

        if (pageId > d_pages.size()) {
            std::cerr << "Invalid Page Access" << std::endl;
            return std::shared_ptr<Page>(nullptr);
        }
        if (d_pages[pageId]->isUnloaded()) {
            //cache miss
            BinarySerializer<Page, int> serializer(d_directory);
            std::shared_ptr<Page> page(new Page(pageId));
            serializer.deserialize(const_cast<std::shared_ptr<Page> &>(d_pages[pageId]), pageId);
        }
        return d_pages[pageId];
    }

    DataContainer::DataContainer(const std::string& fileDirectory, std::vector<std::shared_ptr<Page>> &pages, int numRows,
                                 const std::shared_ptr<MetaDataStore> &metaDataStore) : d_pages(pages),
                                                                                        d_numRows(numRows),
                                                                                        d_directory(
                                                                                                fileDirectory),
                                                                                        d_MetaSerializer(
                                                                                                BinarySerializer<MetaDataStore, std::string>(
                                                                                                        fileDirectory)),
                                                                                        d_dataSerializer(
                                                                                                BinarySerializer<Page, int>(
                                                                                                        fileDirectory)),
                                                                                        d_metaStore(metaDataStore) {
        d_MetaSerializer.serialize(metaDataStore, "index");

    }

    std::shared_ptr<DataRow> DataContainer::getRow(uint32_t cellNumber) const {
        int pageId = d_metaStore->getMapping(cellNumber);
        if (pageId==-1) {
            return nullptr;
        }
        std::shared_ptr<Page> page = getLoadedPage(pageId);
        return page->getRow(cellNumber);
    }


}