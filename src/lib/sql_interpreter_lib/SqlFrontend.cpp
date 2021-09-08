#include "SqlFrontend.h"
#include <iostream>
#include <string>

namespace SQLInterpreter {

    bool SqlFrontend::execute(const Statement &s, SQLCore::DataTable& dataTable) {
        auto cursor = SQLCore::Cursor(dataTable);
        if (s.statementType() == Statement::STATEMENT_SELECT) {
            return executeSelectStatement(s, cursor);
        } else if (s.statementType() == Statement::STATEMENT_INSERT) {
            return executeInsertStatement(s, cursor);
        } else {
            std::cout << "Unknown SQL command." << std::endl;
            return false;
        }
    }

    bool SqlFrontend::executeInsertStatement(const Statement &s, SQLCore::Cursor &cursor) {
        std::vector<std::string> dataParts;
        if (!(SQLInterpreter::InsertStatement::extract(dataParts, s.statementString()))) {
            return false;
        }
        if (!(SQLInterpreter::InsertStatement::validate(dataParts))) {
           return false;
        }
        if (d_table.isFull()) {
            std::cout << "Error: Table full." << std::endl;
            return false;
        }
        if (d_table.getRow(static_cast<uint32_t>(std::stoi(dataParts[1])))) {
            std::cout << "Error: Duplicate key.." << std::endl;
            return false;
        }
        d_queue.addToQueue(s);
        std::cout << "Executed." << std::endl;
        return true;
    }

    bool SqlFrontend::executeSelectStatement(const Statement &s, SQLCore::Cursor &cursor) const {
        std::vector<std::string> statementParts;
        if (!SelectStatement::extract(statementParts, s.statementString())) {
            return false;
        }
        if (!SelectStatement::validate(statementParts)) {
            return false;
        }
        std::vector<std::shared_ptr<SQLCore::DataRow>> results;
        if (statementParts.size() == 6) {
            int id;
            id = std::stoi(statementParts[statementParts.size() - 1]);
            cursor.advance(id);
            std::shared_ptr<SQLCore::DataRow> dataRow = cursor.cursorValue();
            if (dataRow != nullptr) {
                std::cout << std::string(*(dataRow)) << std::endl;
            }
                //move cursor to the position
            else {
                return false;
            }

        } else {
            while (!cursor.isEnd()) {
                cursor.advance();
                std::shared_ptr<SQLCore::DataRow> dataRow = cursor.cursorValue();
                std::cout << std::string(*(dataRow)) << std::endl;
            }
        }

        std::cout << "Executed." << std::endl;
        return true;
    }

    SqlFrontend::SqlFrontend(WALLogger::WalQueue<SQLInterpreter::Statement>& queue, SQLCore::DataTable& table) :d_queue(queue), d_table(table) {
    }

}