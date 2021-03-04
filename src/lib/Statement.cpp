#include "Statement.h"


namespace SQLInterpreter {
    Statement::Statement(const std::string& statementString): d_statementString(statementString),
                                                              d_StatementType(deduceType(statementString))
    {
    }



    const Statement::StatementType Statement::deduceType(const std::string &statementString) const {
        std::unordered_map<std::string,StatementType> statementMap = { {"select",STATEMENT_SELECT}, {"insert",STATEMENT_INSERT} };
        std::string firstWord = statementString.substr(0, statementString.find(" "));
        auto it = statementMap.find(firstWord);
        if (it != statementMap.end()) {
            return it->second;
        } else {
            return STATEMENT_UNKNOWN;
        }
    }

    const bool Statement::extractDataForInsert(std::vector<std::string>& result) {
        std::string remainingWordsString = d_statementString.substr(d_statementString.find(" "),d_statementString.length());
        std::string delimiter = " ";
        Utilities::Utils::split(remainingWordsString, delimiter, result);
        if (result.size() != 4) {
            std::cerr << "Invalid insert statement." << std::endl;
            return false;
        }

        return true;
    };
}