#ifndef SQLLITECLONE_SQLFRONTEND_H
#define SQLLITECLONE_SQLFRONTEND_H

#include <unordered_map>
#include <string>
#include <memory>
#include "../sql_core_lib/DataTable.h"
#include "Statement.h"
#include "../sql_core_lib/Cursor.h"

namespace SQLCore {
    class Cursor;
    class DataTable;
    class DataRow;
}

namespace SQLInterpreter {
    class SqlFrontend {
    public:
        SqlFrontend();
        SqlFrontend& operator=(const SqlFrontend& other)=delete;
        SqlFrontend(const SqlFrontend& other)=delete;
        bool execute(const Statement& s);

    private:
        std::shared_ptr<SQLCore::DataTable> d_dataTable;
        bool executeSelectStatement(const Statement &s, std::shared_ptr<SQLCore::Cursor> &cursor) const;
        bool executeInsertStatement(const Statement &s);
    };

}


#endif //SQLLITECLONE_SQLFRONTEND_H
