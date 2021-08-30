#ifndef SQLLITECLONE_STATEMENT_H
#define SQLLITECLONE_STATEMENT_H

#include <string>
#include <unordered_map>
#include "../sql_core_lib/Utils.h"

namespace SQLInterpreter {
    class Statement {
    public:
        typedef enum {
            STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_UNKNOWN
        } StatementType;
        Statement();
        explicit Statement(const std::string &statementString);
        inline const std::string statementString() const { return d_statementString;};
        [[nodiscard]] inline const StatementType statementType() const { return d_StatementType; };
    private:
        std::string d_statementString;
        StatementType d_StatementType;
        [[nodiscard]] StatementType deduceType(const std::string &statementString) const;
    };

    class SelectStatement {
    public:
            static bool extract(std::vector<std::string> &result, const std::string &statementString);
            static bool validate( std::vector<std::string>& dataParts);

    };

    class InsertStatement  {
    public:
            static bool extract(std::vector<std::string> &result, const std::string &statementString);
            static bool validate(std::vector<std::string>& dataParts);
    };
}



#endif //SQLLITECLONE_STATEMENT_H
