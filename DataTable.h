#ifndef SQLLITECLONE_DATATABLE_H
#define SQLLITECLONE_DATATABLE_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <array>
#include <iostream>



namespace SQLInterpreter {


// Idea is to use std::map which is a balanced btree to store objects using
// Primary Key -> DataRow
// Right now this will be only an in memory append only DB



const int COLUMN_USERNAME_SIZE=255;
const int COLUMN_EMAIL_SIZE=255;
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

class DataRow {
public:
    DataRow(uint32_t id, std::string username, std::string email);
    explicit operator std::string() const;
private:
    uint32_t d_id;
    std::string d_username;
    std::string d_email;
};

const uint32_t ROW_SIZE = sizeof(DataRow);

const int MAX_PAGE_SIZE = 4096;
const int TABLE_MAX_PAGES = 100;
const uint32_t ROWS_PER_PAGE = MAX_PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

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

};

std::shared_ptr<Page> getNewPage();

class DataContainer{
public:
    DataContainer():d_pages(std::vector<std::shared_ptr<Page>>{}){};
    const bool addRow(std::shared_ptr<DataRow> dataRow);
    void rows(std::vector<std::shared_ptr<DataRow>>& results) const;
private:
    std::vector<std::shared_ptr<Page>> d_pages;
};
std::shared_ptr<DataContainer> getDataContainerFactory();

class DataTable {
public:
    DataTable() :d_dataContainer(getDataContainerFactory()){};
    bool insert(std::shared_ptr<DataRow> dataRow);
    inline const bool isFull() const {return numRows==TABLE_MAX_ROWS;};
    bool fetchData(std::vector<std::shared_ptr<DataRow>>& results);
private:
    std::shared_ptr<DataContainer> d_dataContainer;
    uint32_t numRows;
};
}


#endif //SQLLITECLONE_DATATABLE_H
