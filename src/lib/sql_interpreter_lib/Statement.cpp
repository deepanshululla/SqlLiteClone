#include "Statement.h"
#include <regex>

namespace SQLInterpreter {
    Statement::Statement(const std::string &statementString) : d_statementString(statementString),
                                                               d_StatementType(deduceType(statementString)) {
    }


    Statement::StatementType Statement::deduceType(const std::string &statementString) const {
        std::unordered_map<std::string, StatementType> statementMap = {{"select", STATEMENT_SELECT},
                                                                       {"insert", STATEMENT_INSERT}};
        std::string firstWord = statementString.substr(0, statementString.find(" "));
        auto it = statementMap.find(firstWord);
        if (it != statementMap.end()) {
            return it->second;
        } else {
            return STATEMENT_UNKNOWN;
        }
    }

    Statement::Statement() :d_statementString(), d_StatementType(STATEMENT_UNKNOWN){

    }

    bool SelectStatement::extract(std::vector<std::string> &result, const std::string& statementString) {
        std::string delimiter = " ";
        Utilities::Utils::split(statementString, delimiter, result);
        return true;
    }

    bool SelectStatement::validate(std::vector<std::string> &dataParts) {
        if (dataParts.size()<=1) {
            std::cout <<"Invalid select statement. Valid syntax is `select *`" << std::endl;
            return false;
        }
        if (dataParts.size()==6) {
            std::string id = dataParts[dataParts.size()-1];
            if (id.find('-') == 0) {
                std::cout << "ID must be positive." << std::endl;
                return false;
            }
            return true;
        }
        if (dataParts.size()==2 && dataParts[1] != "*") {
          return true;
        }
        return true;
    };

    bool InsertStatement::validate(std::vector<std::string> &dataParts) {
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
        return true;
    }

    bool InsertStatement::extract(std::vector<std::string> &result, const std::string& statementString) {
        std::string delimiter = " ";
        Utilities::Utils::split(statementString, delimiter, result);
        if (result.size() != 4) {
            std::cerr << "Invalid insert statement." << std::endl;
            return false;
        }
        return true;
    }
}