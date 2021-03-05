#include "SqlFrontend.h"
#include <iostream>
#include <string>

namespace SQLInterpreter {

    bool SqlFrontend::execute(Statement s) {
        SQLCore::Cursor cursor = SQLCore::Cursor(d_dataTable);

        if (s.statementType() == Statement::STATEMENT_SELECT) {
            std::vector<std::shared_ptr<SQLCore::DataRow>> results;
            if (cursor.isEnd()) {
                std::cout << "Failed to find data" << std::endl;
                return false;
            }
            while (!cursor.isEnd()) {
                std::shared_ptr<SQLCore::DataRow> dataRow = cursor.cursorValue();
                std::cout << std::string(*(dataRow)) << std::endl;
                cursor.advance();
            }

            std::cout << "Select statement executed" << std::endl;
            return true;


        } else if (s.statementType() == Statement::STATEMENT_INSERT) {
            std::vector<std::string> dataParts;
            if (!s.extractDataForInsert(dataParts)) {
                return false;
            }

            std::shared_ptr<SQLCore::DataRow> dataRow(
                    new SQLCore::DataRow(static_cast<uint32_t>(std::stoi(dataParts[1])),
                                         dataParts[2],
                                         dataParts[3]));
            d_dataTable->insert(dataRow);
            std::cout << "Insert statement executed" << std::endl;
            return true;
        } else {
            std::cout << "Unknown SQL command" << std::endl;
            return false;
        }
    }

    SqlFrontend::SqlFrontend() : d_dataTable(SQLCore::getDataTableFactory()) {
    };


}