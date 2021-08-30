#ifndef SQLLITECLONE_PAGE_H
#define SQLLITECLONE_PAGE_H
// Before including any cereal header file
#define CEREAL_THREAD_SAFE 1
#include <memory>
#include <map>
#include "DataRow.h"


namespace SQLCore {
    const uint32_t ROW_SIZE = sizeof(DataRow);

    const int MAX_PAGE_SIZE = 4096;
    const int TABLE_MAX_PAGES = 19;
    const uint32_t ROWS_PER_PAGE = MAX_PAGE_SIZE / ROW_SIZE;

    class Page {
    public:
        Page(uint32_t id);
        Page(const Page& other)=delete;
        Page& operator=(const Page& other)=delete;
        Page(uint32_t id, std::map<uint32_t,std::shared_ptr<DataRow>> &rows);

        inline const bool isUnloaded() const { return d_isUnloaded; };

        inline const bool isFull() const { return d_rows.size() == ROWS_PER_PAGE; };

        bool addRow(const std::shared_ptr<DataRow>& dataRow);

        std::shared_ptr<DataRow> getRow(uint32_t id) const;

        inline const int id() const { return d_id; };

        inline const std::vector<std::shared_ptr<DataRow>> rows() const {
            std::vector<std::shared_ptr<DataRow>> result{};
            for (auto row : d_rows) {
                result.push_back(row.second);
            }
            return result;
        }

        template<class Archive>
        void serialize(Archive &archive) {
            archive(d_id, d_rows);  // Simply list all the fields to be serialized/deserialized.
        }

        template<class Archive>
        static void load_and_construct(Archive &ar, cereal::construct<Page> &construct) {
            int id;
            std::map<uint32_t,std::shared_ptr<DataRow>> args;
            ar(id, args);
            construct(id, args);
        }

    private:
        std::map<uint32_t,std::shared_ptr<DataRow>> d_rows;
        int d_id;
        bool d_isUnloaded;

    };

    std::shared_ptr<Page> getNewPage(int id);
};
#endif //SQLLITECLONE_PAGE_H
