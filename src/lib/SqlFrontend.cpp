#include "SqlFrontend.h"
#include <iostream>
#include <string>

namespace SQLInterpreter {

bool SqlFrontend::execute(Statement s) {

if (s.statementType()==Statement::STATEMENT_SELECT){
    std::vector<std::shared_ptr<SQLCore::DataRow>> results;

    if (!d_dataTable->fetchData(results)) {
        std::cout << "Failed to find data" << std::endl;
    };
    for (auto it = results.begin(); it!=results.end(); ++it) {
        std::shared_ptr<SQLCore::DataRow> dataRow = *it;
        std::cout << std::string(*(dataRow)) << std::endl;
    }

    std::cout << "Select statement executed" << std::endl;
    return true;
}
else if (s.statementType()==Statement::STATEMENT_INSERT) {
    std::vector<std::string> dataParts;
    if (!s.extractDataForInsert(dataParts)){
     return false;
    }

    std::shared_ptr<SQLCore::DataRow> dataRow(new SQLCore::DataRow(static_cast<uint32_t>(std::stoi(dataParts[1])),
                                                 dataParts[2],
                                                 dataParts[3]));
    d_dataTable->insert(dataRow);
    std::cout << "Insert statement executed" << std::endl;
    return true;
}
else {
    std::cout << "Unknown SQL command" << std::endl;
    return false;
}
}

SqlFrontend::SqlFrontend() :d_dataTable(std::make_shared<SQLCore::DataTable>(SQLCore::DataTable())){
};

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
    result = split(remainingWordsString, delimiter);
    if (result.size() != 4) {
        std::cerr << "Invalid insert statement." << std::endl;
        return false;
    }

    return true;
};

std::vector<std::string> split(std::string& s, std::string& delimiter){
        std::vector<std::string> list;
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            list.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        list.push_back(s);
        return list;
}
}