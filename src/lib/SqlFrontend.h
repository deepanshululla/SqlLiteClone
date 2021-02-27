#ifndef SQLLITECLONE_SQLFRONTEND_H
#define SQLLITECLONE_SQLFRONTEND_H

#include <unordered_map>
#include <string>
#include <memory>
#include "DataTable.h"


namespace SQLCore {
    class DataTable;
    class DataRow;
}

namespace SQLInterpreter {


class Statement {
public:

    typedef enum { STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_UNKNOWN} StatementType;
    explicit Statement(const std::string& statementString);
    [[nodiscard]] inline const StatementType& statementType() const { return d_StatementType;};
    const bool extractDataForInsert(std::vector<std::string>& result);
private:
    std::string d_statementString;
    StatementType d_StatementType;
    [[nodiscard]] const StatementType deduceType(const std::string& statementString) const;


};
std::vector<std::string> split(std::string& s, std::string& delimiter);
class SqlFrontend {

public:
    SqlFrontend();
    typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;
    bool execute(Statement s);

private:
    std::shared_ptr<SQLCore::DataTable> d_dataTable;
};

}


#endif //SQLLITECLONE_SQLFRONTEND_H
