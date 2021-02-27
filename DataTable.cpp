#include "DataTable.h"

namespace SQLInterpreter {


DataRow::DataRow(uint32_t uniqueId, std::string username, std::string email) :d_id(uniqueId), d_username(username), d_email(email){

}



std::shared_ptr<DataContainer> getDataContainerFactory() {
    std::shared_ptr<DataContainer> dataContainer(new DataContainer);
    return dataContainer;
}

std::shared_ptr<Page> getNewPage() {
    std::shared_ptr<Page> page(new Page);
    return page;
}

DataRow::operator std::string() const {
    return "DataRow(" + std::to_string(d_id)+","+d_email+","+d_username + ")";
}

bool DataTable::insert(std::shared_ptr<DataRow> dataRow) {
    if (isFull()) {
        std::cout << "Data table is full."<<std::endl;
        return false;
    }
    d_dataContainer->addRow(dataRow);
    ++numRows;
    return true;
}

bool DataTable::fetchData(std::vector<std::shared_ptr<DataRow>> &results) {
    d_dataContainer->rows(results);
    if (results.empty()) {
        return false;
    }
    return true;
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


bool Page::addRow(std::shared_ptr<DataRow> dataRow) {
    d_rows.push_back(dataRow);
    return true;
}

Page::Page() :d_rows(std::vector<std::shared_ptr<DataRow>>{}){

}
}; //DBCore