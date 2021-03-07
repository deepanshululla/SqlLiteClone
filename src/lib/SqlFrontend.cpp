#include "SqlFrontend.h"
#include <iostream>
#include <string>

namespace SQLInterpreter {

    bool SqlFrontend::execute(Statement s) {
        std::shared_ptr<SQLCore::Cursor> cursor = SQLCore::getCursor(d_dataTable);

        if (s.statementType() == Statement::STATEMENT_SELECT) {
            std::vector<std::shared_ptr<SQLCore::DataRow>> results;
            while (!cursor->isEnd()) {
                std::shared_ptr<SQLCore::DataRow> dataRow = cursor->cursorValue();
                std::cout << std::string(*(dataRow)) << std::endl;
                cursor->advance();
            }

            std::cout << "Executed." << std::endl;
            return true;
        } else if (s.statementType() == Statement::STATEMENT_INSERT) {
            std::vector<std::string> dataParts;
            if (!s.extractDataForInsert(dataParts)) {
                return false;
            }
            std::string id = dataParts[1];

            if (id.find('-') == 0) {
                std::cout << "ID must be positive." << std::endl;
                return false;
            }
            std::string email = dataParts[2];
            std::string userName = dataParts[3];
            if (email.length() > 255 || userName.length() > 255) {
                std::cout << "String is too long." << std::endl;
                return false;
            }



            std::shared_ptr<SQLCore::DataRow> dataRow(
                    new SQLCore::DataRow(static_cast<uint32_t>(std::stoi(id)),
                                         email,
                                         userName));

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
    };


}