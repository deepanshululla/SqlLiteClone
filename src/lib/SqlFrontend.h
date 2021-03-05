#ifndef SQLLITECLONE_SQLFRONTEND_H
#define SQLLITECLONE_SQLFRONTEND_H

#include <unordered_map>
#include <string>
#include <memory>
#include "DataTable.h"
#include "Statement.h"
#include "Cursor.h"

namespace SQLCore {
    class Cursor;

    class DataTable;

    class DataRow;
}

namespace SQLInterpreter {
    class SqlFrontend {
    public:
        SqlFrontend();

        bool execute(Statement s);

    private:
        std::shared_ptr<SQLCore::DataTable> d_dataTable;
    };

}


#endif //SQLLITECLONE_SQLFRONTEND_H
