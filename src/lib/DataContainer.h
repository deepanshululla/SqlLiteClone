#ifndef SQLLITECLONE_DATACONTAINER_H
#define SQLLITECLONE_DATACONTAINER_H

#include "Page.h"
#include "Serializer.h"

namespace SQLCore {
    class DataContainer{
    public:
        DataContainer():d_pages(std::vector<std::shared_ptr<Page>>{}), d_dataSerializer(getSerializer("/Users/deepanshululla/CLionProjects/sqlLiteClone/db.bin")){};
        const bool addRow(std::shared_ptr<DataRow> dataRow);
        void rows(std::vector<std::shared_ptr<DataRow>>& results) const;
    private:
        std::vector<std::shared_ptr<Page>> d_pages;
        std::shared_ptr<Serializer<DataRow>> d_dataSerializer;
    };
    std::shared_ptr<DataContainer> getDataContainerFactory();
}

#endif //SQLLITECLONE_DATACONTAINER_H
