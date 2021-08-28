#include "SqlFrontend.h"
#include <iostream>
#include <string>

namespace SQLInterpreter {

    bool SqlFrontend::execute(const Statement& s) {
        std::shared_ptr<SQLCore::Cursor> cursor = SQLCore::getCursor(d_dataTable);
        if (s.statementType() == Statement::STATEMENT_SELECT) {
            std::vector<std::string> statementParts;
            if (!SelectStatement::extract(statementParts, s.statementString())) {
                return false;
            }
            if (!SelectStatement::validate(statementParts)) {
                return false;
            }
            std::vector<std::shared_ptr<SQLCore::DataRow>> results;
            if (statementParts.size()==6) {
                int id;
                id = std::stoi(statementParts[statementParts.size()-1]);
                cursor->advance(id);
                std::shared_ptr<SQLCore::DataRow> dataRow = cursor->cursorValue();
                if (dataRow!=nullptr) {
                    std::cout << std::string(*(dataRow)) << std::endl;
                }
                    //move cursor to the position
                else {
                    return false;
                }

            }
            else {
                while (!cursor->isEnd()) {
                    cursor->advance();
                    std::shared_ptr<SQLCore::DataRow> dataRow = cursor->cursorValue();
                    std::cout << std::string(*(dataRow)) << std::endl;

                }
            }

            std::cout << "Executed." << std::endl;
            return true;
        }
        else if (s.statementType() == Statement::STATEMENT_INSERT) {

            std::vector<std::string> dataParts;
            if (!(InsertStatement::extract(dataParts, s.statementString()))) {
                return false;
            }

            if (!(InsertStatement::validate(dataParts))) {
                return false;
            }
            std::shared_ptr<SQLCore::DataRow> dataRow(
                    new SQLCore::DataRow(static_cast<uint32_t>(std::stoi(dataParts[1])),
                                         dataParts[2],
                                         dataParts[3]));
            if (d_dataTable->insert(dataRow)){
                std::cout << "Executed." << std::endl;
            }
            return true;
        } else {
            std::cout << "Unknown SQL command." << std::endl;
            return false;
        }
    }

    SqlFrontend::SqlFrontend() : d_dataTable(SQLCore::getDataTableFactory()) {
    }

}