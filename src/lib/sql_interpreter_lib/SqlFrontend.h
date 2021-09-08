#ifndef SQLLITECLONE_SQLFRONTEND_H
#define SQLLITECLONE_SQLFRONTEND_H

#include <unordered_map>
#include <string>
#include <memory>
#include "../sql_core_lib/DataTable.h"
#include "Statement.h"
#include "../sql_core_lib/Cursor.h"
#include "../wal_logger_lib/WalQueue.h"

namespace SQLCore {
    class Cursor;
    class DataTable;
    class DataRow;
}

namespace SQLInterpreter {
    class SqlFrontend {
    public:
        SqlFrontend(WALLogger::WalQueue<SQLInterpreter::Statement>& queue, SQLCore::DataTable& d_table, bool isSingleThreaded=false);
        SqlFrontend& operator=(const SqlFrontend& other)=delete;
        SqlFrontend(const SqlFrontend& other)=delete;
        bool execute(const Statement& s,  SQLCore::DataTable& dataTable);

    private:
        WALLogger::WalQueue<SQLInterpreter::Statement>& d_queue;
        SQLCore::DataTable& d_table;
        bool d_is_single_threaded;
        bool executeSelectStatement(const Statement &s,  SQLCore::Cursor &cursor) const;
        bool executeInsertStatement(const Statement &s,  SQLCore::Cursor &cursor);

    };
    bool executeInsertImpl(const Statement &s, SQLCore::Cursor &cursor);

}



#endif //SQLLITECLONE_SQLFRONTEND_H
