#ifndef SQLLITECLONE_STATEMENT_H
#define SQLLITECLONE_STATEMENT_H

#include <string>
#include <unordered_map>
#include "Utils.h"

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
}



#endif //SQLLITECLONE_STATEMENT_H
