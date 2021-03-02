#ifndef SQLLITECLONE_DATACONTAINER_H
#define SQLLITECLONE_DATACONTAINER_H

//#include "Page.h"
#include <iostream>
#include "Serializer.h"

namespace SQLCore {
    class DataContainer{
    public:
        DataContainer();
        const bool addRow(std::shared_ptr<DataRow>& dataRow);
        void rows(std::vector<std::shared_ptr<DataRow>>& results) const;
    private:
        std::vector<std::shared_ptr<Page>> d_pages;
        std::shared_ptr<Serializer<Page>> d_dataSerializer;
    };
    std::shared_ptr<DataContainer> getDataContainerFactory();
}

#endif //SQLLITECLONE_DATACONTAINER_H
